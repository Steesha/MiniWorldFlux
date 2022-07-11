#pragma once
#include "AbstractModule.h"
#include "EventManager.h"
#include "Game.h"
#include "ProtectDestroyer.h"
#include "Forwards.hpp"
#include "ModeValue.h"

class FakeMessenger : public AbstractModule {

public:

	static FakeMessenger* getInstance();

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

	FakeMessenger();
	DefaultDeconstructor(FakeMessenger);
	NoMoveConstructor(FakeMessenger);
	NoCopyConstructor(FakeMessenger);
	NoAssignOperator(FakeMessenger);

};



