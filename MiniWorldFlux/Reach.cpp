#include "pch.h"
#include "Reach.h"

Reach::Reach() : AbstractModule("Reach", Category::Combat) {
	VM_TIGER_WHITE_START
	this->reachChecker.init(ToPointer(Client::hWorld + Offsets::getOffset(Of_Reach) ^ Client::_XorKey, unsigned char), 1);
	VM_TIGER_WHITE_END
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
	VM_TIGER_WHITE_START
	bool res = Memory::write<unsigned char>(Client::hWorld + Offsets::getOffset(Of_Reach) ^ Client::_XorKey, 0x74);
	VM_TIGER_WHITE_END
	this->reachChecker.restore();

	return res;
}

void Reach::endReach() {

	this->reachChecker.destroy();
	VM_TIGER_WHITE_START
	Memory::write<unsigned char>(Client::hWorld + Offsets::getOffset(Of_Reach) ^ Client::_XorKey, 0x75);
	VM_TIGER_WHITE_END
	this->reachChecker.restore();

}
