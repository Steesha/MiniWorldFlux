#include "pch.h"
#include "NoFall.h"

NoFall::NoFall() : AbstractModule("NoFall", Category::Player) {
	VM_TIGER_WHITE_START
	this->nofallProtect.init(ToPointer(Client::hWorld + Offsets::getOffset(Of_NoFall) ^ Client::_XorKey, void), 1);
	VM_TIGER_WHITE_END
}

NoFall* NoFall::getInstance() {
	static NoFall* inst = new NoFall();
	return inst;
}

void NoFall::onEnabled() {
	VM_TIGER_WHITE_START
	this->nofallProtect.destroy();
	Memory::write<unsigned char>(Client::hWorld + Offsets::getOffset(Of_NoFall) ^ Client::_XorKey, 0);
	this->nofallProtect.restore();
	VM_TIGER_WHITE_END
}

void NoFall::onDisabled() {
	VM_TIGER_WHITE_START
	this->nofallProtect.destroy();
	Memory::write<unsigned char>(Client::hWorld + Offsets::getOffset(Of_NoFall) ^ Client::_XorKey, 1);
	this->nofallProtect.restore();
	VM_TIGER_WHITE_END
}
