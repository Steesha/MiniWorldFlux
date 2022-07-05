#pragma once
#include "AbstractModule.h"
#include "EventManager.h"
#include "Utility.h"
#include "ImGuiHeader.h"
#include "Game.h"
#include "KeyboardSimulator.h"
#include "TimerUtil.h"


class Fly : public AbstractModule {

public:

	static Fly* getInstance();

	void onEnabled();
	void onDisabled();

	void onRenderOverlay();

	bool bypassAC();
	void resetAC();

private:

	Fly();
	DefaultDeconstructor(Fly);
	NoMoveConstructor(Fly);
	NoCopyConstructor(Fly);
	NoAssignOperator(Fly);

};

