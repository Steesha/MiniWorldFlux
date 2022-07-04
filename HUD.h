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
	FloatValue* alOffsetY = new FloatValue("ArrayList Y Offset", 15, 0, 20);
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

