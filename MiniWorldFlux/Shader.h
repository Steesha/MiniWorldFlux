#pragma once
#include "AbstractModule.h"
#include "EventManager.h"
#include "BooleanValue.h"
#include "FloatValue.h"

class Shader : public AbstractModule {

public:

	static Shader* getInstance();

	void onEnabled();
	void onDisabled();

	bool disaledZBuffer();
	bool wireframeMode();
	bool colorMode();
	uint32_t getColor();

private:

	BooleanValue* disableZBuffer = new BooleanValue("Disable ZBuffer", false);
	BooleanValue* wireframe = new BooleanValue("WireFrame", false);
	BooleanValue* color = new BooleanValue("Pure Color", true);
	FloatValue* colR = new FloatValue("R", 250, 0, 255);
	FloatValue* colG = new FloatValue("G", 0, 0, 255);
	FloatValue* colB = new FloatValue("B", 0, 0, 255);
	FloatValue* colA = new FloatValue("A", 230, 0, 255);

	Shader();
	DefaultDeconstructor(Shader);
	NoMoveConstructor(Shader);
	NoCopyConstructor(Shader);
	NoAssignOperator(Shader);

};
