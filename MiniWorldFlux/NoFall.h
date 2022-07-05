#pragma once
#include "AbstractModule.h"
#include "Utility.h"
#include "Game.h"
#include "ProtectDestroyer.h"

class NoFall : public AbstractModule {

public:

	static NoFall* getInstance();

	void onEnabled();
	void onDisabled();

private:

	Memory::ProtectDestroyer nofallProtect;

	NoFall();
	DefaultDeconstructor(NoFall);
	NoMoveConstructor(NoFall);
	NoCopyConstructor(NoFall);
	NoAssignOperator(NoFall);

};