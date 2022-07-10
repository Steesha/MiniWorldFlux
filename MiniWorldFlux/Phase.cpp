#include "pch.h"
#include "Phase.h"

Phase::Phase() : AbstractModule("Phase", Category::Player) {
	this->addrProtect.init(ToPointer(Client::hWorld + Offsets::getOffset(Of_Phase) ^ Client::_XorKey, Address), 6);
}

Phase* Phase::getInstance() {
	static Phase* inst = new Phase();
	return inst;
}

void Phase::onEnabled() {
	this->addrProtect.destroy();
	Memory::write<unsigned char>(Client::hWorld + Offsets::getOffset(Of_Phase) ^ Client::_XorKey + 0, 0x90);
	Memory::write<unsigned char>(Client::hWorld + Offsets::getOffset(Of_Phase) ^ Client::_XorKey + 1, 0x90);
	Memory::write<unsigned char>(Client::hWorld + Offsets::getOffset(Of_Phase) ^ Client::_XorKey + 2, 0x90);
	Memory::write<unsigned char>(Client::hWorld + Offsets::getOffset(Of_Phase) ^ Client::_XorKey + 3, 0x90);
	Memory::write<unsigned char>(Client::hWorld + Offsets::getOffset(Of_Phase) ^ Client::_XorKey + 4, 0x90);
	Memory::write<unsigned char>(Client::hWorld + Offsets::getOffset(Of_Phase) ^ Client::_XorKey + 5, 0x90);
	this->addrProtect.restore();
}

void Phase::onDisabled() {
	this->addrProtect.destroy();
	Memory::write<unsigned char>(Client::hWorld + Offsets::getOffset(Of_Phase) ^ Client::_XorKey + 0, 0x0F);
	Memory::write<unsigned char>(Client::hWorld + Offsets::getOffset(Of_Phase) ^ Client::_XorKey + 1, 0x84);
	Memory::write<unsigned char>(Client::hWorld + Offsets::getOffset(Of_Phase) ^ Client::_XorKey + 2, 0x39);
	Memory::write<unsigned char>(Client::hWorld + Offsets::getOffset(Of_Phase) ^ Client::_XorKey + 3, 0xFE);
	Memory::write<unsigned char>(Client::hWorld + Offsets::getOffset(Of_Phase) ^ Client::_XorKey + 4, 0xFF);
	Memory::write<unsigned char>(Client::hWorld + Offsets::getOffset(Of_Phase) ^ Client::_XorKey + 5, 0xFF);
	this->addrProtect.restore();
}
