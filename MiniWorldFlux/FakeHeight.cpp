#include "pch.h"
#include "FakeHeight.h"

FakeHeight::FakeHeight() : AbstractModule("FakeHeight", Category::Player) {
	this->addValue(this->height);
	EventManager::getInstance().reg(Events::EventRenderOverlay, MakeHandler(this, &FakeHeight::onRenderOverlay));
}

FakeHeight* FakeHeight::getInstance() {
	static FakeHeight* inst = new FakeHeight();
	return inst;
}

void FakeHeight::onEnabled() {
	VM_TIGER_WHITE_START
	this->originScaling = Game::thePlayer->getModelScaling();
	VM_TIGER_WHITE_END
}

void FakeHeight::onDisabled() {
	VM_TIGER_WHITE_START
	Game::thePlayer->setModelScaling(this->originScaling);
	this->originScaling = 0.0f;
	VM_TIGER_WHITE_END
}

void FakeHeight::onRenderOverlay() {
	ToggleCheck;
	IngameCheck;

	Game::thePlayer->setModelScaling(this->height->getValue());

}
