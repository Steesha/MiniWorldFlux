#pragma once
#include "AbstractModule.h"
#include "EventManager.h"
#include "Utility.h"
#include "ImGuiHeader.h"
#include "Game.h"

class TargetHUD : public AbstractModule {

public:

	static TargetHUD* getInstance();

	void onEnabled();
	void onDisabled();

	void onRenderOverlay();

private:

	SDK::ClientPlayer* target = nullptr;

	TargetHUD();
	DefaultDeconstructor(TargetHUD);
	NoMoveConstructor(TargetHUD);
	NoCopyConstructor(TargetHUD);
	NoAssignOperator(TargetHUD);

};