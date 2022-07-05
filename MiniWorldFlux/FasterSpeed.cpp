#include "FasterSpeed.h"

FasterSpeed::FasterSpeed() : AbstractModule("FasterSpeed", Category::Movement) {

	this->addValue(this->walkSpeed);
	this->addValue(this->sprintSpeed);
	this->addValue(this->sneakSpeed);
	this->addValue(this->swimSpeed);

	EventManager::getInstance().reg(Events::EventRenderOverlay, MakeHandler(this, &FasterSpeed::onRenderOverlay));
}

FasterSpeed* FasterSpeed::getInstance() {
	static FasterSpeed* inst = new FasterSpeed();
	return inst;
}

void FasterSpeed::onEnabled() {
		
}

void FasterSpeed::onDisabled() {
	IngameCheck;
		
	Game::thePlayer->setWalkSpeed(-1);
	Game::thePlayer->setRunSpeed(-1);
	Game::thePlayer->setSneakSpeed(-1);
	Game::thePlayer->setSwimSpeed(-1);
		
}

void FasterSpeed::onRenderOverlay() {
	ToggleCheck;
	IngameCheck;

	float walkSpeed = this->walkSpeed->getValue();
	float sprintSpeed = this->sprintSpeed->getValue();
	float sneakSpeed = this->sneakSpeed->getValue();
	float swimSpeed = this->swimSpeed->getValue();
	
	if (Game::thePlayer->getWalkSpeed() != walkSpeed)
		Game::thePlayer->setWalkSpeed(walkSpeed);

	if (Game::thePlayer->getRunSpeed() != sprintSpeed)
		Game::thePlayer->setRunSpeed(sprintSpeed);

	if (Game::thePlayer->getSneakSpeed() != sneakSpeed)
		Game::thePlayer->setSneakSpeed(sneakSpeed);

	if (Game::thePlayer->getSwimSpeed() != swimSpeed)
		Game::thePlayer->setSwimSpeed(swimSpeed);

}
