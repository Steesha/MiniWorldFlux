#include "pch.h"
#include "FakeMessager.h"

namespace FakeMessagerParams {
	
	static DWORD sysModeRetnAddr = 0;
	static DWORD playerModeRetnAddr = 0;
	static int fakeTargetUID = 0;

}

FORWARDS_FN_START(detourFMSYS) {

	__asm {
	
		push 2
		push ebx
		mov ecx,edi
		call dword ptr[eax+0xDC]

	}
	
	FORWARDS_FN_END(FakeMessagerParams::sysModeRetnAddr)
}

FORWARDS_FN_START(detourFMPLAYER) {
	
	__asm {
		
		mov ecx,FakeMessagerParams::fakeTargetUID
		mov eax,[eax+04]
		xor eax,ecx

	}

	FORWARDS_FN_END(FakeMessagerParams::playerModeRetnAddr)
}

FakeMessager::FakeMessager() : AbstractModule("FakeMessager", Category::World) {
	VM_TIGER_WHITE_START

	this->sysModeCodeProtect.init(ToPointer(Client::hWorld + (Offsets::getOffset(Of_FakeMessager_System) ^ Client::_XorKey), Address), 6);
	this->sysModeCodeForwards.init(Client::hWorld + (Offsets::getOffset(Of_FakeMessager_System) ^ Client::_XorKey), ToAddress(detourFMSYS));

	this->playerModeCodeProtect.init(ToPointer(Client::hWorld + (Offsets::getOffset(Of_FakeMessager_Player) ^ Client::_XorKey), Address), 6);
	this->playerModeCodeForwards.init(Client::hWorld + (Offsets::getOffset(Of_FakeMessager_Player) ^ Client::_XorKey), ToAddress(detourFMPLAYER));

	FakeMessagerParams::sysModeRetnAddr = Client::hWorld + (Offsets::getOffset(Of_FakeMessager_System_Retn) ^ Client::_XorKey);
	FakeMessagerParams::playerModeRetnAddr = Client::hWorld + (Offsets::getOffset(Of_FakeMessager_Player_Retn) ^ Client::_XorKey);

	this->sysModeHook = false;
	this->playerModeHook = false;

	this->mode->addMode("Player");
	this->addValue(this->mode);

	EventManager::getInstance().reg(Event::EventRenderOverlay, MakeHandler(this, &FakeMessager::onRenderOverlay));

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

}

void FakeMessager::onDisabled() {
	
	if (this->sysModeHook)
		this->resetSystemMode();
	if (this->playerModeHook)
		this->resetPlayerMode();

}

void FakeMessager::onRenderOverlay() {
	IngameCheck;

	if (this->mode->isCurrentMode("System")) {
	
		if (!this->sysModeHook)
			this->forwardSystemMode();
		if (this->playerModeHook)
			this->resetPlayerMode();

	}
	else if (this->mode->isCurrentMode("Player")) {

		if (!this->playerModeHook)
			this->forwardPlayerMode();
		if (this->sysModeHook)
			this->resetSystemMode();
		
		ImGui::SetNextWindowCollapsed(false, ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2(485, 110), ImGuiCond_Always);
		ImGui::Begin("FakeMessager", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
		ImGui::InputInt("Target UID", &FakeMessagerParams::fakeTargetUID);
		ImGui::End();

	}

}

bool FakeMessager::check() {
	IngameCheck false;
	return Game::theRoomManager->permission == SDK::PERMISSION_ROOMMEMBER 
		|| Game::theRoomManager->permission == SDK::PERMISSION_ROOMADMIN;
}

void FakeMessager::forwardSystemMode() {
	this->sysModeCodeProtect.destroy();
	this->sysModeCodeForwards.forward();
	this->sysModeCodeProtect.restore();
	this->sysModeHook = true;
}

void FakeMessager::forwardPlayerMode() {
	this->playerModeCodeProtect.destroy();
	this->playerModeCodeForwards.forward();
	this->playerModeCodeProtect.restore();
	this->playerModeHook = true;
}

void FakeMessager::resetSystemMode() {
	this->sysModeCodeProtect.destroy();
	this->sysModeCodeForwards.reset();
	this->sysModeCodeProtect.restore();
	this->sysModeHook = false;
}

void FakeMessager::resetPlayerMode() {
	this->playerModeCodeProtect.destroy();
	this->playerModeCodeForwards.reset();
	this->playerModeCodeProtect.restore();
	this->playerModeHook = false;
}



