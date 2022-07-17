#pragma once

#include "AbstractModule.h"
#include "EventManager.h"
#include "Utility.h"
#include "Game.h"
#include "ProtectDestroyer.h"

class FastSkill : public AbstractModule
{
public:
	static FastSkill* getInstance();

	void onEnabled();
	void onDisabled();

private:
	Memory::ProtectDestroyer fastSkillChecker;

	FastSkill();
	DefaultDeconstructor(FastSkill);
	NoMoveConstructor(FastSkill);
	NoCopyConstructor(FastSkill);
	NoAssignOperator(FastSkill);
};

