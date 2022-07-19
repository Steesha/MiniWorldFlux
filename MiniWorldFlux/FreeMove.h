#pragma once
#include "AbstractModule.h"
#include "EventManager.h"
#include "Game.h"
#include "ProtectDestroyer.h"

class FreeMove : public AbstractModule
{
public:
	static FreeMove* getInstance();

	void onEnabled();
	void onDisabled();

private:
	Memory::ProtectDestroyer codeProtect;

	FreeMove();
	DefaultDeconstructor(FreeMove);
	NoMoveConstructor(FreeMove);
	NoCopyConstructor(FreeMove);
	NoAssignOperator(FreeMove);
};

