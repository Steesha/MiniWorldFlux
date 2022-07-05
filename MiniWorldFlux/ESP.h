#pragma once
#include "AbstractModule.h"
#include "EventManager.h"
#include "ImGuiHeader.h"
#include "Game.h"
#include "BooleanValue.h"

class ESP : public AbstractModule {

public:

	static ESP* getInstance();

	void onEnabled();
	void onDisabled();

	void onRenderOverlay();

private:

	BooleanValue* health = new BooleanValue("Health", true);

	ESP();
	DefaultDeconstructor(ESP);
	NoMoveConstructor(ESP);
	NoCopyConstructor(ESP);
	NoAssignOperator(ESP);

};

