#pragma once
#include "AbstractModule.h"
#include "EventManager.h"
#include "Game.h"
#include "FloatValue.h"

class FastBullet : public AbstractModule {

public:

	static FastBullet* getInstance();

	void onEnabled();
	void onDisabled();

private:

	bool start = false;
	short originInterval = 0;
	FloatValue* interval = new FloatValue("Shoot Interval", 1, 1, 200);

	FastBullet();
	DefaultDeconstructor(FastBullet);
	NoMoveConstructor(FastBullet);
	NoCopyConstructor(FastBullet);
	NoAssignOperator(FastBullet);

};

