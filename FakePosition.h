#pragma once

#include "AbstractModule.h"
#include "EventManager.h"
#include "Utility.h"
#include "ImGuiHeader.h"
#include "Game.h"

class FakePosition : public AbstractModule {

public:

	float aimRange = 190;
	float headOffset = 130;

	static FakePosition* getInstance();

	void onEnabled();
	void onDisabled();

private:

	bool faked = false;

	bool startFakePosition();
	void endFakePosition();

	FakePosition();
	DefaultDeconstructor(FakePosition);
	NoMoveConstructor(FakePosition);
	NoCopyConstructor(FakePosition);
	NoAssignOperator(FakePosition);

};

