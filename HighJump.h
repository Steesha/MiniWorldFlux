#pragma once
#include "AbstractModule.h"
#include "Game.h"
#include "EventManager.h"
#include "FloatValue.h"

class HighJump : public AbstractModule {

public:

	static HighJump* getInstance();

	void onEnabled();
	void onDisabled();

	void onRenderOverlay();

private:

	FloatValue* jumpHeight = new FloatValue("Jump Height", 75, -1, 200);

	HighJump();
	DefaultDeconstructor(HighJump);
	NoMoveConstructor(HighJump);
	NoCopyConstructor(HighJump);
	NoAssignOperator(HighJump);

};

