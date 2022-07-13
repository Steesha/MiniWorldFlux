#pragma once
#include "AbstractModule.h"
#include "Utility.h"
#include "Game.h"
#include "FloatValue.h"

class FakeHeight : public AbstractModule {

public:

	static FakeHeight* getInstance();

	void onEnabled();
	void onDisabled();

	void onRenderOverlay();

private:

	float originScaling = 0;
	FloatValue* height = new FloatValue("Height", 5.0f, -30.0f, 30.0f);

	FakeHeight();
	DefaultDeconstructor(FakeHeight);
	NoMoveConstructor(FakeHeight);
	NoCopyConstructor(FakeHeight);
	NoAssignOperator(FakeHeight);

};