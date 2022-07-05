#pragma once
#include "AbstractModule.h"
#include "EventManager.h"
#include "Utility.h"
#include "ImGuiHeader.h"
#include "Game.h"

class IDProtection : public AbstractModule {

public:

	static IDProtection* getInstance();

	void onEnabled();
	void onDisabled();

	void onRenderOverlay();

private:

	IDProtection();
	DefaultDeconstructor(IDProtection);
	NoMoveConstructor(IDProtection);
	NoCopyConstructor(IDProtection);
	NoAssignOperator(IDProtection);

};

