#include "Phase.h"

Phase::Phase() : AbstractModule("Phase", Category::Player) {

	EventManager::getInstance().reg(Event::EventRenderOverlay, MakeHandler(this, &Phase::onRenderOverlay));
}

Phase* Phase::getInstance() {
	static Phase* inst = new Phase();
	return inst;
}

void Phase::onEnabled() {
	Game::thePlayer->setPhaseState(255);
}

void Phase::onDisabled() {
	Game::thePlayer->setPhaseState(256);
}

void Phase::onRenderOverlay() {
	ToggleCheck;
	IngameCheck;

	if (Game::thePlayer->getPhaseState() != 255)
		Game::thePlayer->setPhaseState(255);
}
