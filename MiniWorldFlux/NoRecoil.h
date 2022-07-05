#pragma once

#include "AbstractModule.h"
#include "EventManager.h"
#include "Utility.h"
#include "Game.h"
#include "ProtectDestroyer.h"

class NoRecoil : public AbstractModule {

public:

	static NoRecoil* getInstance();

	void onEnabled();
	void onDisabled();

private:

	Memory::ProtectDestroyer noRecoilChecker;
	Memory::ProtectDestroyer noSpreadChecker;

	NoRecoil();
	DefaultDeconstructor(NoRecoil);
	NoMoveConstructor(NoRecoil);
	NoCopyConstructor(NoRecoil);
	NoAssignOperator(NoRecoil);

};

