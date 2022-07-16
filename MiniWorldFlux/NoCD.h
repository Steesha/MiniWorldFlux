#pragma once

#include "AbstractModule.h"
#include "EventManager.h"
#include "Utility.h"
#include "Game.h"
#include "ProtectDestroyer.h"

class NoCD : public AbstractModule
{
public:
	static NoCD* getInstance();

	void onEnabled();
	void onDisabled();

private:
	NoCD();

	Memory::ProtectDestroyer noCDChecker;
	DefaultDeconstructor(NoCD);
	NoMoveConstructor(NoCD);
	NoCopyConstructor(NoCD);
	NoAssignOperator(NoCD);
};

