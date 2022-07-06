#include "pch.h"
#include "Reach.h"

Reach::Reach() : AbstractModule("Reach", Category::Combat) {
	this->reachChecker.init(ToPointer(Client::hWorld + Offsets::Reach, unsigned char), 1);
}

Reach* Reach::getInstance() {
	static Reach* inst = new Reach();
	return inst;
}

void Reach::onEnabled() {
	IngameCheck;

	this->preGameMode = Game::theWorld->worldManager->mode;
	Game::theWorld->worldManager->mode = SDK::MODE_EDIT;
	this->startReach();

}

void Reach::onDisabled() {
	IngameCheck;

	this->endReach();
	Game::theWorld->worldManager->mode = this->preGameMode;
	this->preGameMode = -1;
	
}

bool Reach::startReach() {

	this->reachChecker.destroy();
	bool res = Memory::write<unsigned char>(Client::hWorld + Offsets::Reach, 0x74);
	this->reachChecker.restore();

	return res;
}

void Reach::endReach() {

	this->reachChecker.destroy();
	Memory::write<unsigned char>(Client::hWorld + Offsets::Reach, 0x75);
	this->reachChecker.restore();

}
