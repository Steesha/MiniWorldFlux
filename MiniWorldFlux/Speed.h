#pragma once

#include "AbstractModule.h"
#include "Game.h"
#include "EventManager.h"
#include "FloatValue.h"
#include "ModeValue.h"

class Speed : public AbstractModule {

public:

	static Speed* getInstance();

	void onEnabled();
	void onDisabled();

	void onRenderOverlay();

private:

	FloatValue* walkSpeed = new FloatValue("Walking Speed", 22, -1, 100);
	FloatValue* sprintSpeed = new FloatValue("Sprinting Speed", 22, -1, 100);
	FloatValue* sneakSpeed = new FloatValue("Sneaking Speed", 22, -1, 100);
	FloatValue* swimSpeed = new FloatValue("Swimming Speed", 22, -1, 100);
	FloatValue* hopForce = new FloatValue("Hop Force", 60, 40, 160);
	FloatValue* forwardForce = new FloatValue("Forward Force", 2.0f, 1.0f, 5.0f);

	ModeValue* mode = new ModeValue("Mode", "Speed");

	Speed();
	DefaultDeconstructor(Speed);
	NoMoveConstructor(Speed);
	NoCopyConstructor(Speed);
	NoAssignOperator(Speed);

};

