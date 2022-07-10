#include "pch.h"
#include "FakeMessager.h"

namespace FakeMessagerParams {
	
	static DWORD retnAddr = 0;

}

FORWARDS_FN_START(detourFM) {

	__asm {
	
		push 2
		push ebx
		mov ecx,edi
		call dword ptr[eax+0xDC]

	}
	
	FORWARDS_FN_END(FakeMessagerParams::retnAddr)
}

FakeMessager::FakeMessager() : AbstractModule("FakeMessager", Category::World) {
	VM_TIGER_WHITE_START
	this->codeProtect.init(ToPointer(Client::hWorld + Offsets::getOffset(Of_FakeMessager) ^ Client::_XorKey, Address), 6);
	this->codeForwards.init(Client::hWorld + Offsets::getOffset(Of_FakeMessager) ^ Client::_XorKey, ToAddress(detourFM));

	FakeMessagerParams::retnAddr = Client::hWorld + Offsets::getOffset(Of_FakeMessagerRetn) ^ Client::_XorKey;
	this->hook = false;
	VM_TIGER_WHITE_END
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
		this->codeForwards.forward();
		this->codeProtect.restore();
		this->hook = true;
	}
}

void FakeMessager::onDisabled() {
	if (this->hook) {
		this->codeProtect.destroy();
		this->codeForwards.reset();
		this->codeProtect.restore();
		this->hook = false;
	}
}

bool FakeMessager::check() {
	IngameCheck false;
	return Game::theRoomManager->permission == SDK::PERMISSION_ROOMMEMBER 
		|| Game::theRoomManager->permission == SDK::PERMISSION_ROOMADMIN;
}


