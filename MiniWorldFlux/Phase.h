#pragma once

#include "AbstractModule.h"
#include "EventManager.h"
#include "Game.h"
#include "ProtectDestroyer.h"

class Phase : public AbstractModule {

public:

	static Phase* getInstance();

	void onEnabled();
	void onDisabled();

private:

	Memory::ProtectDestroyer addrProtect;

	Phase();
	DefaultDeconstructor(Phase);
	NoMoveConstructor(Phase);
	NoCopyConstructor(Phase);
	NoAssignOperator(Phase);

};

