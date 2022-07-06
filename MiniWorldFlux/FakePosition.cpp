#include "pch.h"
#include "FakePosition.h"

FakePosition::FakePosition() : AbstractModule("FakePosition", Category::Player) {

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
		
		Utility::notice("FakePositionÊ§°Ü!", Level::ERR);
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

	DWORD oldProtect = 0;
	VirtualProtect(ToPointer(Client::hWorld + Offsets::FakePosition, void), 2, PAGE_EXECUTE_READWRITE, &oldProtect);
	bool res = Memory::write<unsigned char>(Client::hWorld + Offsets::FakePosition, 0x90) && Memory::write<unsigned char>(Client::hWorld + Offsets::FakePosition + 1, 0x90);
	VirtualProtect(ToPointer(Client::hWorld + Offsets::FakePosition, void), 2, oldProtect, nullptr);

	return res;
}

void FakePosition::endFakePosition() {

	DWORD oldProtect = 0;
	VirtualProtect(ToPointer(Client::hWorld + Offsets::FakePosition, void), 2, PAGE_EXECUTE_READWRITE, &oldProtect);
	Memory::write<unsigned char>(Client::hWorld + Offsets::FakePosition, 0x75);
	Memory::write<unsigned char>(Client::hWorld + Offsets::FakePosition + 1, 0x0C);
	VirtualProtect(ToPointer(Client::hWorld + Offsets::FakePosition, void), 2, oldProtect, nullptr);
}
