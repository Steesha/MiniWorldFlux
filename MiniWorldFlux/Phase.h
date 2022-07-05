#pragma once

#include "AbstractModule.h"
#include "EventManager.h"
#include "Utility.h"
#include "ImGuiHeader.h"
#include "Game.h"

class Phase : public AbstractModule {

public:

	static Phase* getInstance();

	void onEnabled();
	void onDisabled();

	void onRenderOverlay();

private:

	Phase();
	DefaultDeconstructor(Phase);
	NoMoveConstructor(Phase);
	NoCopyConstructor(Phase);
	NoAssignOperator(Phase);

};

