#pragma once
#include <vector>
#include <unordered_map>
#include "GameStructs.h"
#include "Structs.h"
#include "Memory.hpp"
#include "ProtectDestroyer.h"
#include "Client.h"
#include "Offsets.h"
#include "AbstractModule.h"
#include "NotificationManager.h"

using Address = unsigned long;
using Pointer = unsigned long;
using Byte = unsigned char;

#define IngameCheck if (!Game::isPlaying()) return
#define SinglePlayerCheck if (Game::singlePlayerChecker()) return

#pragma region LocalPlayer

class LocalPlayer {

public:

	float matrix[4][4];

	static LocalPlayer* getInstance();
	
	bool syncData();
	Address getAddress();

	Vec3 getPosition();
	Vec3 getCameraPosition();

	float getWalkSpeed();
	bool setWalkSpeed(float speed);

	float getRunSpeed();
	bool setRunSpeed(float speed);

	float getSneakSpeed();
	bool setSneakSpeed(float speed);

	float getSwimSpeed();
	bool setSwimSpeed(float speed);

	float getJumpHeight();
	bool setJumpHeight(float height);

	float getCurrentHealth();
	float getMaxHealth();
	float getCurrentOxygen();
	float getCurrentHunger();
	float getMaxHunger();

	int getJumpState();
	bool setJumpState(int state);

	int getFlyState();
	bool setFlyState(int state);

	float getYaw();
	float getPitch();
	bool setYaw(float yaw);
	bool setPitch(float pitch);

	int getPhaseState();
	bool setPhaseState(int state);

	int getCrossPointTo();
	bool setCrossPointTo(int pointTo);

	int getTeam();

	int getFOV();

	int getUID();

	SDK::Weapon* getWeapon();

	SDK::ClientPlayer* getObject();
	
private:

	// Data
	SDK::ClientPlayer* obj = nullptr;

	DefaultConstructor(LocalPlayer);
	DefaultDeconstructor(LocalPlayer);
	NoMoveConstructor(LocalPlayer);
	NoCopyConstructor(LocalPlayer);
	NoAssignOperator(LocalPlayer);

};

#pragma endregion

namespace Game {

	extern LocalPlayer* thePlayer;
	extern SDK::World* theWorld;
	extern SDK::UIRenderer* theUIRenderer;
	extern SDK::RoomManager* theRoomManager;

	extern std::vector<SDK::ClientPlayer*> playerInWorld;
	extern std::unordered_map<int, SDK::PlayerInfo*> playerInfo;

	void updateData();
	bool isPlaying();
	Vec2 getGameViewSize();
	bool singlePlayerChecker();

}


