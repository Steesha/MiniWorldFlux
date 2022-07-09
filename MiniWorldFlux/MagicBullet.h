#pragma once
#include "AbstractModule.h"
#include "EventManager.h"
#include "Game.h"
#include "ProtectDestroyer.h"
#include "Forwards.hpp"

class MagicBullet : public AbstractModule {

public:

	static MagicBullet* getInstance();

	void onEnabled();
	void onDisabled();

private:

	Memory::ProtectDestroyer codeProtect;
	Forwards codeForwards;
	bool hook = false;

	bool adminCheck();

	MagicBullet();
	DefaultDeconstructor(MagicBullet);
	NoMoveConstructor(MagicBullet);
	NoCopyConstructor(MagicBullet);
	NoAssignOperator(MagicBullet);

};



