#pragma once
#include "AbstractModule.h"
#include "Utility.h"
#include "Game.h"
#include "ProtectDestroyer.h"
#include "Forwards.hpp"
#include "ModeValue.h"

class Velocity : public AbstractModule {

public:

	static Velocity* getInstance();

	void onEnabled();
	void onDisabled();

	void onRenderOverlay();

	void enableMemoryMode();
	void disableMemoryMode();
	void forwardForceMode();
	void resetForceMode();

private:

	ModeValue* mode = new ModeValue("Mode", "Memory");
	bool memoryModeEnabled = false;
	bool forceModeEnabled = false;

	Memory::ProtectDestroyer codeProtect;
	Forwards codeForwards;

	Memory::ProtectDestroyer nopCodeProtect;

	Velocity();
	DefaultDeconstructor(Velocity);
	NoMoveConstructor(Velocity);
	NoCopyConstructor(Velocity);
	NoAssignOperator(Velocity);

};