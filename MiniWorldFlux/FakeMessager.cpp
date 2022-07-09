#include "pch.h"
#include "FakeMessager.h"

namespace FakeMessagerParams {
	
	static DWORD retnAddr = 0;

}

__declspec(naked) void detourFM() {
	
	__asm {
		
		push 2
		push ebx
		mov ecx,edi
		call dword ptr [eax+0xDC]
		push [FakeMessagerParams::retnAddr]
		ret

	}

}

FakeMessager::FakeMessager() : AbstractModule("FakeMessager", Category::World) {

	this->codeProtect.init(ToPointer(Client::hWorld + Offsets::getOffset(Of_FakeMessager), Address), 6);

	// Backup
	RtlCopyMemory(&(this->originBytes), ToPointer(Client::hWorld + Offsets::getOffset(Of_FakeMessager), Address), 6);

	// Build
	this->detourBytes[0] = 0x68;
	this->detourBytes[5] = 0xC3;
	DWORD pDetour = ToAddress(detourFM);
	RtlCopyMemory(&(this->detourBytes[1]), &pDetour, 4);

	FakeMessagerParams::retnAddr = Client::hWorld + Offsets::getOffset(Of_FakeMessagerRetn);
	this->hook = false;

}

FakeMessager* FakeMessager::getInstance() {
	static FakeMessager* inst = new FakeMessager();
	return inst;
}

void FakeMessager::onEnabled() {
	
	if (!this->check()) {
		NotificationManager::getInstance().notify("Only for room!", NotiLevel::ERR, 3);
		this->disable();
		return;
	}

	if (!this->hook) {
		this->codeProtect.destroy();
		RtlCopyMemory(ToPointer(Client::hWorld + Offsets::getOffset(Of_FakeMessager), Address), &(this->detourBytes), 6);
		this->codeProtect.restore();
		this->hook = true;
	}
}

void FakeMessager::onDisabled() {
	if (this->hook) {
		this->codeProtect.destroy();
		RtlCopyMemory(ToPointer(Client::hWorld + Offsets::getOffset(Of_FakeMessager), Address), &(this->originBytes), 6);
		this->codeProtect.restore();
		this->hook = false;
	}
}

bool FakeMessager::check() {
	IngameCheck false;
	return Game::theRoomManager->permission == SDK::PERMISSION_ROOMMEMBER 
		|| Game::theRoomManager->permission == SDK::PERMISSION_ROOMADMIN;
}


