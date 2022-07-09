#pragma once
#include "AbstractModule.h"
#include "EventManager.h"
#include "Game.h"
#include "ProtectDestroyer.h"
#include "Forwards.hpp"

class FakeMessager : public AbstractModule {

public:

	static FakeMessager* getInstance();

	void onEnabled();
	void onDisabled();

private:

	Memory::ProtectDestroyer codeProtect;
	Forwards codeForwards;
	bool hook = false;

	bool check();

	FakeMessager();
	DefaultDeconstructor(FakeMessager);
	NoMoveConstructor(FakeMessager);
	NoCopyConstructor(FakeMessager);
	NoAssignOperator(FakeMessager);

};



