#include "pch.h"
#include "FreeMove.h"

FreeMove::FreeMove() : AbstractModule("FreeMove", Category::Player) {
	codeProtect.init(ToPointer(Client::hWorld + (Offsets::getOffset(Of_FreeMove) ^ Client::_XorKey), unsigned char), 1);
}

FreeMove* FreeMove::getInstance() {
	static FreeMove* inst = new FreeMove();
	return inst;
}

void FreeMove::onEnabled() {
	VM_TIGER_WHITE_START

	codeProtect.destroy();
	Memory::write<unsigned char>(Client::hWorld + (Offsets::getOffset(Of_FreeMove) ^ Client::_XorKey), 0xEB);
	codeProtect.restore();

	VM_TIGER_WHITE_END
}

void FreeMove::onDisabled() {
	VM_TIGER_WHITE_START

	codeProtect.destroy();
	Memory::write<unsigned char>(Client::hWorld + (Offsets::getOffset(Of_FreeMove) ^ Client::_XorKey), 0x74);
	codeProtect.restore();

	VM_TIGER_WHITE_END
}