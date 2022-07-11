#pragma once
#include <vector>
#include <algorithm>
#include "AbstractModule.h"
#include "EventManager.h"
#include "ImGuiHeader.h"
#include "Game.h"
#include "BooleanValue.h"
#include "FloatValue.h"
#include "ModeValue.h"

class HUD : public AbstractModule {

public:

	static HUD* getInstance();

	void onEnabled();
	void onDisabled();

	void onRenderOverlay();

private:

	std::vector<HMOD> enabledMods;

	BooleanValue* rainbow = new BooleanValue("Rainbow", true);
	FloatValue* listX = new FloatValue("ArrayList X", 20, 0, 3000);
	FloatValue* listY = new FloatValue("ArrayList Y", 300, 0, 3000);
	ModeValue* mode = new ModeValue("Mode", "Flux");

	HUD();
	DefaultDeconstructor(HUD);
	NoMoveConstructor(HUD);
	NoCopyConstructor(HUD);
	NoAssignOperator(HUD);

};

class EnabledListSorter {

public:
	bool operator()(HMOD m1, HMOD m2);
};

