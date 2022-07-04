#pragma once

#include "AbstractModule.h"
#include "Game.h"
#include "EventManager.h"
#include "FloatValue.h"

class FasterSpeed : public AbstractModule {

public:

	static FasterSpeed* getInstance();

	void onEnabled();
	void onDisabled();

	void onRenderOverlay();

private:

	FloatValue* walkSpeed = new FloatValue("Walking Speed", 22, -1, 100);
	FloatValue* sprintSpeed = new FloatValue("Sprinting Speed", 22, -1, 100);
	FloatValue* sneakSpeed = new FloatValue("Sneaking Speed", 22, -1, 100);
	FloatValue* swimSpeed = new FloatValue("Swimming Speed", 22, -1, 100);

	FasterSpeed();
	DefaultDeconstructor(FasterSpeed);
	NoMoveConstructor(FasterSpeed);
	NoCopyConstructor(FasterSpeed);
	NoAssignOperator(FasterSpeed);

};

