#include "pch.h"
#include "FakePosition.h"

FakePosition::FakePosition() : AbstractModule("FakePosition", Category::Player) {
	addrProtect.init(ToPointer(Client::hWorld + Offsets::getOffset(Of_FakePosition) ^ Client::_XorKey, void), 2);
}

FakePosition* FakePosition::getInstance() {
	static FakePosition* inst = new FakePosition();
	return inst;
}

void FakePosition::onEnabled() {

	if (this->startFakePosition()) {

		this->faked = true;
		if (!Fly::getInstance()->getToggle())
			Fly::getInstance()->enable();

	}
	else {
		
		NotificationManager::getInstance().notify("FakePosition Failed.", NotiLevel::ERR, 3);
		this->faked = false;
		this->disable();

	}

}

void FakePosition::onDisabled() {

	if (this->faked) {
		
		this->endFakePosition();
		if (Fly::getInstance()->getToggle())
			Fly::getInstance()->disable();

	}

}

bool FakePosition::startFakePosition() {
	IngameCheck false;

	this->addrProtect.destroy();
	bool res = Memory::write<unsigned char>(Client::hWorld + Offsets::getOffset(Of_FakePosition) ^ Client::_XorKey, 0x90) && Memory::write<unsigned char>(Client::hWorld + Offsets::getOffset(Of_FakePosition) ^ Client::_XorKey + 1, 0x90);
	this->addrProtect.restore();

	return res;
}

void FakePosition::endFakePosition() {

	this->addrProtect.destroy();
	Memory::write<unsigned char>(Client::hWorld + Offsets::getOffset(Of_FakePosition) ^ Client::_XorKey, 0x75);
	Memory::write<unsigned char>(Client::hWorld + Offsets::getOffset(Of_FakePosition) ^ Client::_XorKey + 1, 0x0C);
	this->addrProtect.restore();

}
