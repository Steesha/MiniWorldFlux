#include "Game.h"

LocalPlayer* LocalPlayer::getInstance() {
	static LocalPlayer* inst = new LocalPlayer();
	return inst;
}

bool LocalPlayer::syncData() {
	IngameCheck false;

	unsigned long* playerList = Game::theWorld->playerList_Level1->playerList;
	if (!Utility::isReadablePtr(playerList)) return false;

	SDK::ClientPlayer* pThePlayer = ToPointer(*playerList, SDK::ClientPlayer);
	if (!Utility::isReadablePtr(pThePlayer)) return false;

	this->obj = pThePlayer;

	if (Utility::isReadablePtr(Game::theUIRenderer)) {
		if (Utility::isReadablePtr(Game::theUIRenderer->matrixLevel1)) {
			if (Utility::isReadablePtr(Game::theUIRenderer->matrixLevel1->matrixLevel2)) {
				RtlCopyMemory(this->matrix, Game::theUIRenderer->matrixLevel1->matrixLevel2->matrix, 64);
				return true;
			}
		}
	}
	
	memset(this->matrix, 1, 64);
	return false;
}

Vec3 LocalPlayer::getPosition() {
	IngameCheck { -1, -1, -1 };

	return { this->obj->actorBody->entity->posX, this->obj->actorBody->entity->posY, this->obj->actorBody->entity->posZ };
}

Vec3 LocalPlayer::getCameraPosition() {
	IngameCheck{ -1, -1, -1 };

	return { this->obj->gameCamera->camera->posX, this->obj->gameCamera->camera->posY, this->obj->gameCamera->camera->posZ };
}

float LocalPlayer::getWalkSpeed() {
	IngameCheck 0;

	return this->obj->playerAttribuLua->walkingSpeed;
}

bool LocalPlayer::setWalkSpeed(float speed) {
	IngameCheck false;

	this->obj->playerAttribuLua->walkingSpeed = speed;
	return true;
}

float LocalPlayer::getRunSpeed() {
	IngameCheck 0;

	return this->obj->playerAttribuLua->runningSpeed;
}

bool LocalPlayer::setRunSpeed(float speed) {
	IngameCheck false;

	this->obj->playerAttribuLua->runningSpeed = speed;
	return true;
}

float LocalPlayer::getSneakSpeed() {
	IngameCheck 0;

	return this->obj->playerAttribuLua->sneakingSpeed;
}

bool LocalPlayer::setSneakSpeed(float speed) {
	IngameCheck false;

	this->obj->playerAttribuLua->sneakingSpeed = speed;
	return true;
}

float LocalPlayer::getSwimSpeed() {
	IngameCheck 0;

	return this->obj->playerAttribuLua->swimmingSpeed;
}

bool LocalPlayer::setSwimSpeed(float speed) {
	IngameCheck false;

	this->obj->playerAttribuLua->swimmingSpeed = speed;
	return true;
}

float LocalPlayer::getJumpHeight() {
	IngameCheck 0;

	return this->obj->playerAttribuLua->jumpHeight;
}

bool LocalPlayer::setJumpHeight(float height) {
	IngameCheck false;

	this->obj->playerAttribuLua->jumpHeight = height;
	return true;
}

float LocalPlayer::getCurrentHealth() {
	IngameCheck 0;
	float health = this->obj->playerAttribuLua->currentHealth;
	health = (health <= 0) ? 0 : health;
	return health;
}

float LocalPlayer::getMaxHealth() {
	IngameCheck 0;
	return this->obj->playerAttribuLua->maxHealth;
}

float LocalPlayer::getCurrentOxygen() {
	IngameCheck 0;
	return this->obj->playerAttribuLua->oxygen;
}

float LocalPlayer::getCurrentHunger() {
	IngameCheck 0;
	return this->obj->playerAttribuLua->currentHunger;
}

float LocalPlayer::getMaxHunger() {
	IngameCheck 0;
	return this->obj->playerAttribuLua->maxHunger;
}

Address LocalPlayer::getAddress() {
	return ToAddress(this->obj);
}

int LocalPlayer::getJumpState() {
	IngameCheck 0;
	return this->obj->playerLocoMotion->onGround;
}

bool LocalPlayer::setJumpState(int state) {
	IngameCheck false;
	this->obj->playerLocoMotion->onGround = state;
	return true;
}

int LocalPlayer::getFlyState() {
	IngameCheck 0;
	return this->obj->flyState;
}

bool LocalPlayer::setFlyState(int state) {
	IngameCheck false;
	this->obj->flyState = state;
	return true;
}

float LocalPlayer::getYaw() {
	IngameCheck 0;
	return this->obj->gameCamera->yaw;
}

float LocalPlayer::getPitch() {
	IngameCheck 0;
	return this->obj->gameCamera->pitch;
}

bool LocalPlayer::setYaw(float yaw) {
	IngameCheck false;

	this->obj->gameCamera->yaw = yaw;
	return true;
}

bool LocalPlayer::setPitch(float pitch) {
	IngameCheck false;

	this->obj->gameCamera->pitch = pitch;
	return true;
}

int LocalPlayer::getPhaseState() {
	IngameCheck 256;
	return this->obj->playerLocoMotion->phase;
}

bool LocalPlayer::setPhaseState(int state) {
	IngameCheck false;

	this->obj->playerLocoMotion->phase = state;
	return true;
}

int LocalPlayer::getCrossPointTo() {
	IngameCheck 0;
	return this->obj->crossPointTo;
}

bool LocalPlayer::setCrossPointTo(int pointTo) {
	IngameCheck false;

	this->obj->crossPointTo = pointTo;
	return true;
}

int LocalPlayer::getTeam() {
	IngameCheck 0;
	return this->obj->playerTeamComponent->team;
}

int LocalPlayer::getFOV() {
	IngameCheck 0;
	return this->obj->gameCamera->fov;
}

int LocalPlayer::getUID() {
	IngameCheck 0;
	return this->obj->uid;
}

SDK::ClientPlayer* LocalPlayer::getObject() {
	IngameCheck nullptr;
	return this->obj;
}

unsigned long g_localPlayer = 0;
unsigned long g_freeItemsCallAddr = 0;

namespace Game {

	LocalPlayer* thePlayer = LocalPlayer::getInstance();
	SDK::World* theWorld = nullptr;
	SDK::UIRenderer* theUIRenderer = nullptr;

	std::vector<SDK::ClientPlayer*> playerInWorld;
	std::unordered_map<int, SDK::PlayerInfo*> playerInfo;

	void updateData() {

		if (!Game::playerInWorld.empty())
			Game::playerInWorld.clear();
		if (!Game::playerInfo.empty())
			Game::playerInfo.clear();

		Game::theWorld = SDK::getWorld();
		if (Game::theWorld == nullptr) return;

		IngameCheck;
		Game::theUIRenderer = SDK::getUIRenderer();
		if (Game::theUIRenderer == nullptr) return;
		
		// 加载地图的所有房间时length会变成-256或者很大的数
		if (Game::theWorld->playerList_Level1->length < 0 || Game::theWorld->playerList_Level1->length > 300) return;

		// 同步自身信息
		if (!Game::thePlayer->syncData()) return;

		// 同步房间内玩家
		for (int i = 1; i < (Game::theWorld->playerList_Level1->length - 1); i++) {

			unsigned long* ppPlayer = Game::theWorld->playerList_Level1->playerList + i;
			if (!Utility::isReadablePtr(ppPlayer)) continue;

			SDK::ClientPlayer* pPlayer = ToPointer(*ppPlayer, SDK::ClientPlayer);
			if (!Utility::isReadablePtr(pPlayer)) continue;

			Game::playerInWorld.push_back(pPlayer);
		}

		// 是否单机
		SinglePlayerCheck;

		// 同步房间内玩家信息
		Address* pPlayerInfoBase = ToPointer(Client::hWorld + Offsets::PlayerInfoBase, Address);
		if (Utility::isReadablePtr(pPlayerInfoBase)) {

			unsigned long* pMpGameSurvive = ToPointer((*pPlayerInfoBase) + Offsets::MpGameSurvive, Address);
			if (Utility::isReadablePtr(pMpGameSurvive)) {
				
				SDK::MpGameSurvive* mpGameSurvive = ToPointer(*pMpGameSurvive, SDK::MpGameSurvive);
				if (Utility::isReadablePtr(mpGameSurvive)) {

					if (Utility::isReadablePtr(mpGameSurvive->playerInfo)) {

						int cur = 0;
						int target = Game::theWorld->playerList_Level1->length - 1;
						for (int i = 0;; i++) {

							unsigned long* ppPlayerInfo = ToPointer(mpGameSurvive->playerInfo + i, Address);
							if (!Utility::isReadablePtr(ppPlayerInfo)) continue;

							SDK::PlayerInfo* pPlayerInfo = ToPointer(*ppPlayerInfo, SDK::PlayerInfo);
							if (!Utility::isReadablePtr(pPlayerInfo)) continue;

							Game::playerInfo.insert(std::pair<int, SDK::PlayerInfo*>(pPlayerInfo->uid, pPlayerInfo));

							++cur;
							if (cur == target || i > target * 2) break;
						}

					}

				}

			}

		}
		
	}

	bool isPlaying() {
		
		if (SDK::getWorld() == nullptr) return false;
		if (!Utility::isReadablePtr(Game::theWorld)) return false;
		if (!Utility::isReadablePtr(Game::theWorld->playerList_Level1)) return false;
		if (!Utility::isReadablePtr(Game::theWorld->playerList_Level1->playerList)) return false;
		if (!Utility::isReadablePtr(Game::theWorld->worldManager)) return false;

		int mode = Game::theWorld->worldManager->mode;
		return (mode >= 1 && mode <=5);
	}

	Vec2 getGameViewSize() {
		return Vec2(Client::rendererIO->DisplaySize.x, Client::rendererIO->DisplaySize.y);
	}

	bool singlePlayerChecker() {
		if (Game::playerInWorld.empty()) return true;
		if (Game::theWorld->playerList_Level1->length <= 1) return true;
		return false;
	}

}
