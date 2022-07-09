#include "pch.h"
#include "MagicBullet.h"

namespace MagicBulletParams {

	static DWORD retnAddr = 0;
	static DWORD worldOffset = 0;

}

__declspec(naked) void detourMB() {
	
	__asm {
	
		push ecx				// Store
		mov ecx,Client::hWorld
		add ecx, MagicBulletParams::worldOffset
		mov ecx,[ecx]
		push [ecx+0x4720]
		mov ecx,0x520				// ?
		pop ecx					// Release

		mov ecx,[ecx+0xC]
		mov ecx,[ecx+0x4]		// 第几(i * 0x04)个人
		mov ecx,[ecx+0x50C]
		add ecx,1

		push ecx				// Store
		sub dword ptr [esp],1
		pop ecx					// Release

		mov eax,[ecx+0x3C]		// posX
		mov [edi+0x3C],eax

		mov eax,[ecx+0x40]		// posY
		add eax,0x70			// 头部偏移
		mov[edi+0x40], eax

		mov eax,[ecx+0x44]		// posZ
		pop ecx					// ?
		mov[edi+0x44], eax

		lea eax,[edi+0x70]

		push [MagicBulletParams::retnAddr]
		ret

	}

}

MagicBullet::MagicBullet() : AbstractModule("MagicBullet", Category::Combat) {

	this->codeProtect.init(ToPointer(Client::hWorld + Offsets::getOffset(Of_MagicBullet), Address), 6);

	// Backup origin code
	RtlCopyMemory(&(this->originBytes), ToPointer(Client::hWorld + Offsets::getOffset(Of_MagicBullet), Address), 6);

	// Build detour code
	this->detourBytes[0] = 0x68;
	this->detourBytes[5] = 0xC3;
	DWORD pDetour = ToAddress(detourMB);
	RtlCopyMemory(&(this->detourBytes[1]), &pDetour, 4);

	MagicBulletParams::worldOffset = Offsets::getOffset(Of_World);
	MagicBulletParams::retnAddr = Client::hWorld + Offsets::getOffset(Of_MagicBulletRetn);
	this->hook = false;

}

MagicBullet* MagicBullet::getInstance() {
	static MagicBullet* inst = new MagicBullet();
	return inst;
}

void MagicBullet::onEnabled() {

	if (!this->adminCheck()) {
		NotificationManager::getInstance().notify("Admin needed!", NotiLevel::ERR, 3);
		this->disable();
		return;
	}

	if (!this->hook) {
		this->codeProtect.destroy();
		RtlCopyMemory(ToPointer(Client::hWorld + Offsets::getOffset(Of_MagicBullet), Address), &(this->detourBytes), 6);
		this->codeProtect.restore();
		this->hook = true;
	}

}

void MagicBullet::onDisabled() {

	if (this->hook) {
		this->codeProtect.destroy();
		RtlCopyMemory(ToPointer(Client::hWorld + Offsets::getOffset(Of_MagicBullet), Address), &(this->originBytes), 6);
		this->codeProtect.restore();
		this->hook = false;
	}
	
}

bool MagicBullet::adminCheck() {
	IngameCheck false;
	return Game::theRoomManager->permission == SDK::PERMISSION_ROOMADMIN;
}
