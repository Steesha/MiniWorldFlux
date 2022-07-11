#pragma once
#include "AbstractModule.h"
#include "EventManager.h"
#include "Utility.h"
#include "ImGuiHeader.h"
#include "Game.h"
#include "ModeValue.h"
#include "BooleanValue.h"

class Aimbot : public AbstractModule {

public:

	float aimRange = 190;
	float headOffset = 130;

	static Aimbot* getInstance();

	void onEnabled();
	void onDisabled();

	void onRenderOverlay();

	SDK::ClientPlayer* getTarget();

private:

	SDK::ClientPlayer* target = nullptr;

	BooleanValue* targetLine = new BooleanValue("Target Line", true);
	ModeValue* priority = new ModeValue("Priority", "Dist2Cross");

	Aimbot();
	DefaultDeconstructor(Aimbot);
	NoMoveConstructor(Aimbot);
	NoCopyConstructor(Aimbot);
	NoAssignOperator(Aimbot);

};

class AimbotDisSorter {

public:
	bool operator()(SDK::ClientPlayer* p1, SDK::ClientPlayer* p2);
};

class AimbotScreenDisSorter {

public:
	bool operator()(SDK::ClientPlayer* p1, SDK::ClientPlayer* p2);
};
