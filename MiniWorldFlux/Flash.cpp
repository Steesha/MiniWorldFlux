#include "pch.h"
#include "Flash.h"

namespace FlashParams
{
	static DWORD retnAddr = 0;
	static DWORD worldOffset = 0;
}

FORWARDS_FN_START(detourF) {

	__asm {

		push eax

		mov eax, Client::hWorld
		add eax, FlashParams::worldOffset
		mov eax, [eax]
		mov eax, [eax + 0x4720]
		mov eax, [eax + 0xC]
		mov eax, [eax]		// eax -> PlayerControlLua

		cmp eax, esi		// eax == esi  则为手持物品 过滤没必要的地址
		pop eax

		jne orgCode
		mov eax, 0x2EE5		// 修改ID为能量剑
		pop ebp
		ret 4

		orgCode:
			mov eax, [eax + 0xA0]
	}

	FORWARDS_FN_END(FlashParams::retnAddr)
}

Flash::Flash() : AbstractModule("Flash", Category::Player) {
	this->codeProtect.init(ToPointer(Client::hWorld + (Offsets::getOffset(Of_Flash) ^ Client::_XorKey), Address), 6);
	this->codeForwards.init(Client::hWorld + (Offsets::getOffset(Of_Flash) ^ Client::_XorKey), ToAddress(detourF));
	FlashParams::retnAddr = Client::hWorld + (Offsets::getOffset(Of_Flash_Retn) ^ Client::_XorKey);
	FlashParams::worldOffset = (Offsets::getOffset(Of_World) ^ Client::_XorKey);
}

Flash* Flash::getInstance() {
	static Flash* inst = new Flash();
	return inst;
}

void Flash::onEnabled() {

	this->codeProtect.destroy();
	this->codeForwards.forward();
	this->codeProtect.restore();
}

void Flash::onDisabled() {

	this->codeProtect.destroy();
	this->codeForwards.reset();
	this->codeProtect.restore();

}
