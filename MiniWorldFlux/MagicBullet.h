#pragma once
#include "AbstractModule.h"
#include "EventManager.h"
#include "Game.h"
#include "ProtectDestroyer.h"

class MagicBullet : public AbstractModule {

public:

	static MagicBullet* getInstance();

	void onEnabled();
	void onDisabled();

private:

	Memory::ProtectDestroyer codeProtect;
	unsigned char originBytes[6] = { 0 };
	unsigned char detourBytes[6] = { 0 };
	bool start = false;

	bool adminCheck();

	MagicBullet();
	DefaultDeconstructor(MagicBullet);
	NoMoveConstructor(MagicBullet);
	NoCopyConstructor(MagicBullet);
	NoAssignOperator(MagicBullet);

};



