#include "HighJump.h"

HighJump::HighJump() : AbstractModule("HighJump", Category::Movement) {
	
	this->addValue(jumpHeight);

	EventManager::getInstance().reg(Events::EventRenderOverlay, MakeHandler(this, &HighJump::onRenderOverlay));
}

HighJump* HighJump::getInstance() {
	static HighJump* inst = new HighJump();
	return inst;
}

void HighJump::onEnabled() {

}

void HighJump::onDisabled() {
	IngameCheck;
	
	Game::thePlayer->setJumpHeight(-1);
}

void HighJump::onRenderOverlay() {
	ToggleCheck;
	IngameCheck;

	float jumpHeight = this->jumpHeight->getValue();

	if (Game::thePlayer->getJumpHeight() != jumpHeight)
		Game::thePlayer->setJumpHeight(jumpHeight);

}
