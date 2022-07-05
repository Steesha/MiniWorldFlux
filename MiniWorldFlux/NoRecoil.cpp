#include "NoRecoil.h"

NoRecoil::NoRecoil() : AbstractModule("NoRecoil", Category::Combat) {
	this->noRecoilChecker.init(ToPointer(Client::hWorld + Offsets::NoRecoil, unsigned char), 1);
	this->noSpreadChecker.init(ToPointer(Client::hWorld + Offsets::NoSpread, unsigned char), 1);
}

NoRecoil* NoRecoil::getInstance() {
	static NoRecoil* inst = new NoRecoil();
	return inst;
}

void NoRecoil::onEnabled() {
	IngameCheck;

	this->noRecoilChecker.destroy();
	this->noSpreadChecker.destroy();
	Memory::write<unsigned char>(Client::hWorld + Offsets::NoRecoil, 0xEB);
	Memory::write<unsigned char>(Client::hWorld + Offsets::NoSpread, 0xEB);
}

void NoRecoil::onDisabled() {
	IngameCheck;

	Memory::write<unsigned char>(Client::hWorld + Offsets::NoRecoil, 0x76);
	Memory::write<unsigned char>(Client::hWorld + Offsets::NoSpread, 0x76);
	this->noRecoilChecker.restore();
	this->noSpreadChecker.restore();
}
