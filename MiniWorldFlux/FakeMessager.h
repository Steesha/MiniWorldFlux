#pragma once
#include "AbstractModule.h"
#include "EventManager.h"
#include "Game.h"
#include "ProtectDestroyer.h"

class FakeMessager : public AbstractModule {

public:

	static FakeMessager* getInstance();

	void onEnabled();
	void onDisabled();

private:

	Memory::ProtectDestroyer codeProtect;
	unsigned char originBytes[6] = { 0 };
	unsigned char detourBytes[6] = { 0 };
	bool hook = false;

	bool check();

	FakeMessager();
	DefaultDeconstructor(FakeMessager);
	NoMoveConstructor(FakeMessager);
	NoCopyConstructor(FakeMessager);
	NoAssignOperator(FakeMessager);

};



