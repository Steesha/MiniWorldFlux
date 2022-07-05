#pragma once
#include "AbstractModule.h"
#include "EventManager.h"
#include "Utility.h"
#include "ImGuiHeader.h"
#include "Game.h"
#include "BooleanValue.h"
#include "FloatValue.h"

class Radar : public AbstractModule {

public:

	static Radar* getInstance();

	void onEnabled();
	void onDisabled();

	void onRenderOverlay();

private:

	BooleanValue* center = new BooleanValue("Center", true);
	BooleanValue* showFOV = new BooleanValue("Show FOV", true);
	FloatValue* scale = new FloatValue("Radar Scale", 0.3f, 0.01f, 2.0f);

	Vec2 scPos;

	Vec2 transformPos(Vec3 self, Vec3 target, float angle, float scale);

	Radar();
	DefaultDeconstructor(Radar);
	NoMoveConstructor(Radar);
	NoCopyConstructor(Radar);
	NoAssignOperator(Radar);

};

