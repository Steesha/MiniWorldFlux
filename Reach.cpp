#include "Reach.h"

Reach::Reach() : AbstractModule("Reach", Category::Combat) {
	this->reachChecker.init(ToPointer(Client::hWorld + Offsets::Reach, unsigned char), 1);
}

Reach* Reach::getInstance() {
	static Reach* inst = new Reach();
	return inst;
}

void Reach::onEnabled() {
	IngameCheck;

	if (Fly::getInstance()->bypassAC()) {
		this->preGameMode = Game::theWorld->worldManager->mode;
		Game::theWorld->worldManager->mode = SDK::MODE_EDIT;
		this->startReach();
	}
	else {
		Utility::notice("绕过飞行反作弊失败，但是可以使用此功能，请不要双击空格进行飞行", Level::ERR);
	}

}

void Reach::onDisabled() {
	IngameCheck;

	this->endReach();
	Game::theWorld->worldManager->mode = this->preGameMode;
	this->preGameMode = -1;
	Fly::getInstance()->resetAC();
}

bool Reach::startReach() {

	bool res = this->reachChecker.destroy();
	if (res)
		res = Memory::write<unsigned char>(Client::hWorld + Offsets::Reach, 0x74);

	return res;
}

void Reach::endReach() {

	this->reachChecker.restore();
	Memory::write<unsigned char>(Client::hWorld + Offsets::Reach, 0x75);
}
