#include "pch.h"
#include "Fly.h"

Fly::Fly() : AbstractModule("Fly", Category::Movement) {
	this->addrProtect.init(ToPointer(Client::hWorld + Offsets::FlyCheck, void), 2);
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

		NotificationManager::getInstance().notify("Fly bypass failed!", NotiLevel::ERR, 3);
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
	
	this->addrProtect.destroy();
	bool res = Memory::write<unsigned char>(Client::hWorld + Offsets::FlyCheck, 0x90) && Memory::write<unsigned char>(Client::hWorld + Offsets::FlyCheck + 1, 0x90);
	this->addrProtect.restore();

	return res;
}

void Fly::resetAC() {

	this->addrProtect.destroy();
	Memory::write<unsigned char>(Client::hWorld + Offsets::FlyCheck, 0x75);
	Memory::write<unsigned char>(Client::hWorld + Offsets::FlyCheck + 1, 0x12);
	this->addrProtect.restore();
}
