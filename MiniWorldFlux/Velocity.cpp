#include "pch.h"
#include "Velocity.h"

namespace VelocityParams {

	static DWORD retnAddress = 0;
	static DWORD locomotion = 0;

}

FORWARDS_FN_START(detourBeHurt) {

	__asm {

		// Orgin
		add esp, 0x08
		push 0x04
		push eax

		// Hook
		push ebx			// Store
		push ecx			// Store
		mov ebx, [VelocityParams::locomotion]
		mov ecx,0x00000000	// 0.00f
		mov [ebx+0x70],ecx
		mov ecx,0xC2480000	// -50.0f
		mov [ebx+0x74],ecx
		mov ecx,0x00000000	// 0.0f
		mov [ebx+0x78],ecx
		pop ecx				// Release
		pop ebx				// Release

	}

	FORWARDS_FN_END(VelocityParams::retnAddress)
}

Velocity::Velocity() : AbstractModule("Velocity", Category::Player) {

	// this->mode->addMode("Memory");
	this->addValue(this->mode);

	this->codeProtect.init(ToPointer(Client::hWorld + (Offsets::getOffset(Of_Velocity) ^ g_XORKEY), Address), 6);
	this->codeForwards.init(Client::hWorld + (Offsets::getOffset(Of_Velocity) ^ g_XORKEY), ToAddress(detourBeHurt));

	VelocityParams::retnAddress = Client::hWorld + (Offsets::getOffset(Of_Velocity_Retn) ^ g_XORKEY);

	this->nopCodeProtect.init(ToPointer(Client::hWorld + (Offsets::getOffset(Of_Velocity_MemoryCode) ^ g_XORKEY), Address), 0x30);

	EventManager::getInstance().reg(Event::EventRenderOverlay, MakeHandler(this, &Velocity::onRenderOverlay));
}

Velocity* Velocity::getInstance() {
	static Velocity* inst = new Velocity();
	return inst;
}

void Velocity::onEnabled() {
	
}

void Velocity::onDisabled() {
	VM_TIGER_WHITE_START

	this->disableMemoryMode();
	this->resetForceMode();

	VM_TIGER_WHITE_END
}

void Velocity::onRenderOverlay() {
	ToggleCheck;
	IngameCheck;

	if (this->mode->isCurrentMode("Force")) {

		VelocityParams::locomotion = reinterpret_cast<DWORD>(Game::thePlayer->getObject()->playerLocoMotion);

		if (!this->forceModeEnabled)
			this->forwardForceMode();
		if (this->memoryModeEnabled)
			this->disableMemoryMode();

	}

	if (this->mode->isCurrentMode("Memory") && (!this->memoryModeEnabled)) {
		
		this->enableMemoryMode();
		if (this->forceModeEnabled)
			this->resetForceMode();

	}


}

void Velocity::enableMemoryMode() {
	this->nopCodeProtect.destroy();
	Address addr = Client::hWorld + (Offsets::getOffset(Of_Velocity_MemoryCode) ^ g_XORKEY);
	Memory::write<unsigned char>(addr + 0, 0x90);
	Memory::write<unsigned char>(addr + 1, 0x90);
	Memory::write<unsigned char>(addr + 2, 0x90);
	Memory::write<unsigned char>(addr + 3, 0x90);
	Memory::write<unsigned char>(addr + 0x15, 0x90);
	Memory::write<unsigned char>(addr + 0x16, 0x90);
	Memory::write<unsigned char>(addr + 0x17, 0x90);
	Memory::write<unsigned char>(addr + 0x18, 0x90);
	Memory::write<unsigned char>(addr + 0x19, 0x90);
	Memory::write<unsigned char>(addr + 0x2B, 0x90);
	Memory::write<unsigned char>(addr + 0x2C, 0x90);
	Memory::write<unsigned char>(addr + 0x2D, 0x90);
	Memory::write<unsigned char>(addr + 0x2E, 0x90);
	Memory::write<unsigned char>(addr + 0x2F, 0x90);
	this->nopCodeProtect.restore();
	this->memoryModeEnabled = true;
}

void Velocity::disableMemoryMode() {
	this->nopCodeProtect.destroy();
	Address addr = Client::hWorld + (Offsets::getOffset(Of_Velocity_MemoryCode) ^ g_XORKEY);
	Memory::write<unsigned char>(addr + 0, 0xF3);
	Memory::write<unsigned char>(addr + 1, 0x0F);
	Memory::write<unsigned char>(addr + 2, 0x11);
	Memory::write<unsigned char>(addr + 3, 0x02);
	Memory::write<unsigned char>(addr + 0x15, 0xF3);
	Memory::write<unsigned char>(addr + 0x16, 0x0F);
	Memory::write<unsigned char>(addr + 0x17, 0x11);
	Memory::write<unsigned char>(addr + 0x18, 0x42);
	Memory::write<unsigned char>(addr + 0x19, 0x04);
	Memory::write<unsigned char>(addr + 0x2B, 0xF3);
	Memory::write<unsigned char>(addr + 0x2C, 0x0F);
	Memory::write<unsigned char>(addr + 0x2D, 0x11);
	Memory::write<unsigned char>(addr + 0x2E, 0x42);
	Memory::write<unsigned char>(addr + 0x2F, 0x08);
	this->nopCodeProtect.restore();
	this->memoryModeEnabled = false;
}

void Velocity::forwardForceMode() {
	this->codeProtect.destroy();
	this->codeForwards.forward();
	this->codeProtect.restore();
	this->forceModeEnabled = true;
}

void Velocity::resetForceMode() {
	this->codeProtect.destroy();
	this->codeForwards.reset();
	this->codeProtect.restore();
	this->forceModeEnabled = false;
}
