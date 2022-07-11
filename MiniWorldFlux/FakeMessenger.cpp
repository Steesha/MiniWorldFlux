#include "pch.h"
#include "FakeMessenger.h"

namespace FakeMessengerParams {
	
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
	
	FORWARDS_FN_END(FakeMessengerParams::sysModeRetnAddr)
}

FORWARDS_FN_START(detourFMPLAYER) {
	
	__asm {
		
		mov ecx, FakeMessengerParams::fakeTargetUID
		mov eax,[eax+04]
		xor eax,ecx

	}

	FORWARDS_FN_END(FakeMessengerParams::playerModeRetnAddr)
}

FakeMessenger::FakeMessenger() : AbstractModule("FakeMessenger", Category::World) {
	VM_TIGER_WHITE_START

	this->sysModeCodeProtect.init(ToPointer(Client::hWorld + (Offsets::getOffset(Of_FakeMessenger_System) ^ Client::_XorKey), Address), 6);
	this->sysModeCodeForwards.init(Client::hWorld + (Offsets::getOffset(Of_FakeMessenger_System) ^ Client::_XorKey), ToAddress(detourFMSYS));

	this->playerModeCodeProtect.init(ToPointer(Client::hWorld + (Offsets::getOffset(Of_FakeMessenger_Player) ^ Client::_XorKey), Address), 6);
	this->playerModeCodeForwards.init(Client::hWorld + (Offsets::getOffset(Of_FakeMessenger_Player) ^ Client::_XorKey), ToAddress(detourFMPLAYER));

	FakeMessengerParams::sysModeRetnAddr = Client::hWorld + (Offsets::getOffset(Of_FakeMessenger_System_Retn) ^ Client::_XorKey);
	FakeMessengerParams::playerModeRetnAddr = Client::hWorld + (Offsets::getOffset(Of_FakeMessenger_Player_Retn) ^ Client::_XorKey);

	this->sysModeHook = false;
	this->playerModeHook = false;

	this->mode->addMode("Player");
	this->addValue(this->mode);

	EventManager::getInstance().reg(Event::EventRenderOverlay, MakeHandler(this, &FakeMessenger::onRenderOverlay));

	VM_TIGER_WHITE_END
}

FakeMessenger* FakeMessenger::getInstance() {
	static FakeMessenger* inst = new FakeMessenger();
	return inst;
}

void FakeMessenger::onEnabled() {
	
	if (!this->check()) {
		NotificationManager::getInstance().notify("Only for room!", NotiLevel::ERR, 3);
		this->disable();
		return;
	}

}

void FakeMessenger::onDisabled() {
	
	if (this->sysModeHook)
		this->resetSystemMode();
	if (this->playerModeHook)
		this->resetPlayerMode();

}

void FakeMessenger::onRenderOverlay() {
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
		ImGui::Begin("FakeMessenger", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
		ImGui::InputInt("Target UID", &FakeMessengerParams::fakeTargetUID);
		ImGui::End();

	}

}

bool FakeMessenger::check() {
	IngameCheck false;
	return Game::theRoomManager->permission == SDK::PERMISSION_ROOMMEMBER 
		|| Game::theRoomManager->permission == SDK::PERMISSION_ROOMADMIN;
}

void FakeMessenger::forwardSystemMode() {
	this->sysModeCodeProtect.destroy();
	this->sysModeCodeForwards.forward();
	this->sysModeCodeProtect.restore();
	this->sysModeHook = true;
}

void FakeMessenger::forwardPlayerMode() {
	this->playerModeCodeProtect.destroy();
	this->playerModeCodeForwards.forward();
	this->playerModeCodeProtect.restore();
	this->playerModeHook = true;
}

void FakeMessenger::resetSystemMode() {
	this->sysModeCodeProtect.destroy();
	this->sysModeCodeForwards.reset();
	this->sysModeCodeProtect.restore();
	this->sysModeHook = false;
}

void FakeMessenger::resetPlayerMode() {
	this->playerModeCodeProtect.destroy();
	this->playerModeCodeForwards.reset();
	this->playerModeCodeProtect.restore();
	this->playerModeHook = false;
}



