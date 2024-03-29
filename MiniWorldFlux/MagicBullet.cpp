#include "pch.h"
#include "MagicBullet.h"

namespace MagicBulletParams {

	static DWORD retnAddr = 0;
	static DWORD worldOffset = 0;

}

FORWARDS_FN_START(detourMB) {
	
	__asm {
		
		push ecx				// Store
		mov ecx,Client::hWorld
		add ecx,MagicBulletParams::worldOffset
		mov ecx,[ecx]
		push[ecx+0x4720]
		mov ecx,0x520				// ?
		pop ecx					// Release

		mov ecx,[ecx+0xC]
		mov ecx,[ecx+0x4]		// 第几(i * 0x04)个人
		mov ecx,[ecx+0x50C]
		add ecx,1

		push ecx				// Store
		sub dword ptr[esp],1
		pop ecx					// Release

		mov eax,[ecx+0x3C]		// posX
		mov[edi+0x3C],eax

		mov eax,[ecx+0x40]		// posY
		add eax,0x70			// 头部偏移
		mov[edi+0x40],eax

		mov eax,[ecx+0x44]		// posZ
		pop ecx					// ?
		mov[edi+0x44],eax

		lea eax,[edi+0x70]

	}

	FORWARDS_FN_END(MagicBulletParams::retnAddr)
}

MagicBullet::MagicBullet() : AbstractModule("MagicBullet", Category::Combat) {
	VM_TIGER_WHITE_START
	this->codeProtect.init(ToPointer(Client::hWorld + (Offsets::getOffset(Of_MagicBullet) ^ Client::_XorKey), Address), 6);
	this->codeForwards.init(Client::hWorld + (Offsets::getOffset(Of_MagicBullet) ^ Client::_XorKey), ToAddress(detourMB));
	MagicBulletParams::worldOffset = (Offsets::getOffset(Of_World) ^ Client::_XorKey);
	MagicBulletParams::retnAddr = Client::hWorld + (Offsets::getOffset(Of_MagicBulletRetn) ^ Client::_XorKey);
	this->hook = false;
	VM_TIGER_WHITE_END
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
		this->codeForwards.forward();
		this->codeProtect.restore();
		this->hook = true;
	}

}

void MagicBullet::onDisabled() {

	if (this->hook) {
		this->codeProtect.destroy();
		this->codeForwards.reset();
		this->codeProtect.restore();
		this->hook = false;
	}
	
}

bool MagicBullet::adminCheck() {
	IngameCheck false;
	if (!Utility::isReadablePtr(Game::theRoomManager)) return false;
	return Game::theRoomManager->permission == SDK::PERMISSION_ROOMADMIN;
}
