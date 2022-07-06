#include "pch.h"
#include "AirJump.h"

AirJump::AirJump() : AbstractModule("AirJump", Category::Movement) {

	EventManager::getInstance().reg(Event::EventRenderOverlay, MakeHandler(this, &AirJump::onRenderOverlay));
}

AirJump* AirJump::getInstance() {
	static AirJump* inst = new AirJump();
	return inst;
}

void AirJump::onEnabled() {
	Game::thePlayer->setJumpState(1);
}

void AirJump::onDisabled() {
	Game::thePlayer->setJumpState(0);
}

void AirJump::onRenderOverlay() {
	ToggleCheck;
	IngameCheck;

	if (Game::thePlayer->getJumpState() != 1)
		Game::thePlayer->setJumpState(1);
}
