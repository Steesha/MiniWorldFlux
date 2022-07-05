#pragma once
#include "AbstractModule.h"
#include "EventManager.h"
#include "Utility.h"
#include "ImGuiHeader.h"
#include "Game.h"
#include "BooleanValue.h"
#include "ModeValue.h"
#include "FloatValue.h"

class BoxESP : public AbstractModule {

public:

	static BoxESP* getInstance();

	void onEnabled();
	void onDisabled();

	void onRenderOverlay();

private:

	BooleanValue* sight = new BooleanValue("Sight", true);
	ModeValue* boxMode = new ModeValue("Render Mode", "Line");
	FloatValue* radius = new FloatValue("Radius", 65.0f, 10.0f, 100.0f);
	FloatValue* ringSpeed = new FloatValue("Ring Speed", 0.5f, 0.01f, 1.0f);

	float headOffset = 190;
	float sightLength = 300;
	float sightXOffset = 125;
	bool direction = true;
	Vec3 curPosition;
	float curYOffset = 0;

	Vec3 rotatePointYaw(Vec3 opc, float radius, float angle);
	Vec3 rotatePointPitch(Vec3 opc, float radius, float angle);

	BoxESP();
	DefaultDeconstructor(BoxESP);
	NoMoveConstructor(BoxESP);
	NoCopyConstructor(BoxESP);
	NoAssignOperator(BoxESP);

};
