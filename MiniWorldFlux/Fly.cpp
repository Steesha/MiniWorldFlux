#include "Fly.h"

Fly::Fly() : AbstractModule("Fly", Category::Movement) {
	EventManager::getInstance().reg(Event::EventRenderOverlay, MakeHandler(this, &Fly::onRenderOverlay));
}

Fly* Fly::getInstance() {
	static Fly* inst = new Fly();
	return inst;
}

void Fly::onEnabled() {

	if (this->bypassAC()) {
		Game::thePlayer->setFlyState(8);
	}
	else {
		Utility::notice("绕过飞行反作弊失败，请勿使用此功能!", Level::ERR);
		this->disable();
	}
}

void Fly::onDisabled() {
	Game::thePlayer->setFlyState(0);
	this->resetAC();
}

void Fly::onRenderOverlay() {
	ToggleCheck;
	IngameCheck;

	if (this->bypassAC() && Game::thePlayer->getFlyState() != 8)
		Game::thePlayer->setFlyState(8);

}

bool Fly::bypassAC() {
	
	DWORD oldProtect = 0;
	VirtualProtect(ToPointer(Client::hWorld + Offsets::FlyCheck, void), 2, PAGE_EXECUTE_READWRITE, &oldProtect);
	bool res = Memory::write<unsigned char>(Client::hWorld + Offsets::FlyCheck, 0x90) && Memory::write<unsigned char>(Client::hWorld + Offsets::FlyCheck + 1, 0x90);
	VirtualProtect(ToPointer(Client::hWorld + Offsets::FlyCheck, void), 2, oldProtect, nullptr);

	return res;
}

void Fly::resetAC() {

	DWORD oldProtect = 0;
	VirtualProtect(ToPointer(Client::hWorld + Offsets::FlyCheck, void), 2, PAGE_EXECUTE_READWRITE, &oldProtect);
	Memory::write<unsigned char>(Client::hWorld + Offsets::FlyCheck, 0x75);
	Memory::write<unsigned char>(Client::hWorld + Offsets::FlyCheck + 1, 0x12);
	VirtualProtect(ToPointer(Client::hWorld + Offsets::FlyCheck, void), 2, oldProtect, nullptr);
}
