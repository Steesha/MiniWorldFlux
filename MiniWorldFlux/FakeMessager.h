#pragma once
#include "AbstractModule.h"
#include "EventManager.h"
#include "Game.h"
#include "ProtectDestroyer.h"
#include "Forwards.hpp"
#include "ModeValue.h"

class FakeMessager : public AbstractModule {

public:

	static FakeMessager* getInstance();

	void onEnabled();
	void onDisabled();

	void onRenderOverlay();

private:

	Memory::ProtectDestroyer sysModeCodeProtect;
	Forwards sysModeCodeForwards;
	Memory::ProtectDestroyer playerModeCodeProtect;
	Forwards playerModeCodeForwards;
	bool sysModeHook = false;
	bool playerModeHook = false;
	ModeValue* mode = new ModeValue("Fake Mode", "System");

	bool check();
	void forwardSystemMode();
	void forwardPlayerMode();
	void resetSystemMode();
	void resetPlayerMode();

	FakeMessager();
	DefaultDeconstructor(FakeMessager);
	NoMoveConstructor(FakeMessager);
	NoCopyConstructor(FakeMessager);
	NoAssignOperator(FakeMessager);

};



