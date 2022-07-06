#pragma once

#include "AbstractModule.h"
#include "EventManager.h"
#include "Utility.h"
#include "ImGuiHeader.h"
#include "Game.h"
#include "ProtectDestroyer.h"

class FakePosition : public AbstractModule {

public:

	static FakePosition* getInstance();

	void onEnabled();
	void onDisabled();

private:

	bool faked = false;
	Memory::ProtectDestroyer addrProtect;

	bool startFakePosition();
	void endFakePosition();

	FakePosition();
	DefaultDeconstructor(FakePosition);
	NoMoveConstructor(FakePosition);
	NoCopyConstructor(FakePosition);
	NoAssignOperator(FakePosition);

};

