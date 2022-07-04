#pragma once
#include "AbstractModule.h"
#include "EventManager.h"
#include "TimerUtil.h"
#include "Game.h"

class FreeItems : public AbstractModule {

public:

	static FreeItems* getInstance();

	void onEnabled();
	void onDisabled();

	void onRenderOverlay();

private:

	int itemId = 15054;
	TimerUtil intervalTimer;

	FreeItems();
	DefaultDeconstructor(FreeItems);
	NoMoveConstructor(FreeItems);
	NoCopyConstructor(FreeItems);
	NoAssignOperator(FreeItems);

};