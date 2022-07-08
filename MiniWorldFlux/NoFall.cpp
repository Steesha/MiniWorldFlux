#include "pch.h"
#include "NoFall.h"

NoFall::NoFall() : AbstractModule("NoFall", Category::Player) {
	this->nofallProtect.init(ToPointer(Client::hWorld + Offsets::getOffset(Of_NoFall), void), 1);
}

NoFall* NoFall::getInstance() {
	static NoFall* inst = new NoFall();
	return inst;
}

void NoFall::onEnabled() {
	this->nofallProtect.destroy();
	Memory::write<unsigned char>(Client::hWorld + Offsets::getOffset(Of_NoFall), 0);
	this->nofallProtect.restore();
}

void NoFall::onDisabled() {
	this->nofallProtect.destroy();
	Memory::write<unsigned char>(Client::hWorld + Offsets::getOffset(Of_NoFall), 1);
	this->nofallProtect.restore();
}
