#pragma once

#include "AbstractModule.h"
#include "EventManager.h"
#include "Utility.h"
#include "ImGuiHeader.h"
#include "Game.h"
#include "ProtectDestroyer.h"


class Reach : public AbstractModule {

public:

	const int MAX_DISTANCE = 3200;

	static Reach* getInstance();

	void onEnabled();
	void onDisabled();

	bool startReach();
	void endReach();

private:

	int preGameMode = -1;
	Memory::ProtectDestroyer reachChecker;

	Reach();
	DefaultDeconstructor(Reach);
	NoMoveConstructor(Reach);
	NoCopyConstructor(Reach);
	NoAssignOperator(Reach);

};

