#pragma once
#include "AbstractModule.h"
#include "EventManager.h"
#include "Game.h"

class Fly : public AbstractModule {

public:

	static Fly* getInstance();

	void onEnabled();
	void onDisabled();

private:

	Fly();
	DefaultDeconstructor(Fly);
	NoMoveConstructor(Fly);
	NoCopyConstructor(Fly);
	NoAssignOperator(Fly);

};

