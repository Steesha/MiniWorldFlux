#include "pch.h"
#include "NoRecoil.h"

NoRecoil::NoRecoil() : AbstractModule("NoRecoil", Category::Combat) {
	VM_TIGER_WHITE_START
	this->noRecoilChecker.init(ToPointer(Client::hWorld + Offsets::getOffset(Of_NoRecoil) ^ Client::_XorKey, unsigned char), 1);
	this->noSpreadChecker.init(ToPointer(Client::hWorld + Offsets::getOffset(Of_NoSpread) ^ Client::_XorKey, unsigned char), 1);
	VM_TIGER_WHITE_END
}

NoRecoil* NoRecoil::getInstance() {
	static NoRecoil* inst = new NoRecoil();
	return inst;
}

void NoRecoil::onEnabled() {
	IngameCheck;
	VM_TIGER_WHITE_START
	this->noRecoilChecker.destroy();
	this->noSpreadChecker.destroy();
	Memory::write<unsigned char>(Client::hWorld + Offsets::getOffset(Of_NoRecoil) ^ Client::_XorKey, 0xEB);
	Memory::write<unsigned char>(Client::hWorld + Offsets::getOffset(Of_NoSpread) ^ Client::_XorKey, 0xEB);
	VM_TIGER_WHITE_END
}

void NoRecoil::onDisabled() {
	IngameCheck;
	VM_TIGER_WHITE_START
	Memory::write<unsigned char>(Client::hWorld + Offsets::getOffset(Of_NoRecoil) ^ Client::_XorKey, 0x76);
	Memory::write<unsigned char>(Client::hWorld + Offsets::getOffset(Of_NoSpread) ^ Client::_XorKey, 0x76);
	this->noRecoilChecker.restore();
	this->noSpreadChecker.restore();
	VM_TIGER_WHITE_END
}
