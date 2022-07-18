#pragma once

#include "AbstractModule.h"
#include "EventManager.h"
#include "Utility.h"
#include "Game.h"
#include "ProtectDestroyer.h"

class Flash : public AbstractModule
{
public:
	static Flash* getInstance();

	void onEnabled();
	void onDisabled();

private:
	Flash();

	Memory::ProtectDestroyer codeProtect;
	Forwards codeForwards;

	DefaultDeconstructor(Flash);
	NoMoveConstructor(Flash);
	NoCopyConstructor(Flash);
	NoAssignOperator(Flash);
};

