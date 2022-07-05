#pragma once
#include "AbstractModule.h"
#include "EventManager.h"
#include "Utility.h"
#include "ImGuiHeader.h"
#include "Game.h"


class AirJump : public AbstractModule {

public:

	static AirJump* getInstance();

	void onEnabled();
	void onDisabled();

	void onRenderOverlay();

private:

	AirJump();
	DefaultDeconstructor(AirJump);
	NoMoveConstructor(AirJump);
	NoCopyConstructor(AirJump);
	NoAssignOperator(AirJump);

};

