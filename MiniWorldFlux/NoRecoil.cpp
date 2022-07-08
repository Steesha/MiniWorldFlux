#include "pch.h"
#include "NoRecoil.h"

NoRecoil::NoRecoil() : AbstractModule("NoRecoil", Category::Combat) {
	this->noRecoilChecker.init(ToPointer(Client::hWorld + Offsets::getOffset(Of_NoRecoil), unsigned char), 1);
	this->noSpreadChecker.init(ToPointer(Client::hWorld + Offsets::getOffset(Of_NoSpread), unsigned char), 1);
}

NoRecoil* NoRecoil::getInstance() {
	static NoRecoil* inst = new NoRecoil();
	return inst;
}

void NoRecoil::onEnabled() {
	IngameCheck;

	this->noRecoilChecker.destroy();
	this->noSpreadChecker.destroy();
	Memory::write<unsigned char>(Client::hWorld + Offsets::getOffset(Of_NoRecoil), 0xEB);
	Memory::write<unsigned char>(Client::hWorld + Offsets::getOffset(Of_NoSpread), 0xEB);
}

void NoRecoil::onDisabled() {
	IngameCheck;

	Memory::write<unsigned char>(Client::hWorld + Offsets::getOffset(Of_NoRecoil), 0x76);
	Memory::write<unsigned char>(Client::hWorld + Offsets::getOffset(Of_NoSpread), 0x76);
	this->noRecoilChecker.restore();
	this->noSpreadChecker.restore();
}
