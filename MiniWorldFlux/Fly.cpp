#include "pch.h"
#include "Fly.h"

Fly::Fly() : AbstractModule("Fly", Category::Movement) {

}

Fly* Fly::getInstance() {
	static Fly* inst = new Fly();
	return inst;
}

void Fly::onEnabled() {
	Game::thePlayer->setFlyState(8);
}

void Fly::onDisabled() {
	Game::thePlayer->setFlyState(0);
}
