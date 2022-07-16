#include "pch.h"
#include "NoCD.h"

NoCD::NoCD() : AbstractModule("NoCD", Category::Combat)
{
	noCDChecker.init(ToPointer(Client::hWorld + (Offsets::getOffset(Of_NoCD) ^ Client::_XorKey), unsigned char), 2);
}

NoCD* NoCD::getInstance()
{
	static NoCD* inst = new NoCD();
	return inst;
}

void NoCD::onEnabled()
{
	IngameCheck;
	noCDChecker.destroy();
	Memory::write<unsigned char>(Client::hWorld + (Offsets::getOffset(Of_NoCD) ^ Client::_XorKey) + 0, 0x3C);
	Memory::write<unsigned char>(Client::hWorld + (Offsets::getOffset(Of_NoCD) ^ Client::_XorKey) + 1, 0x09);
}

void NoCD::onDisabled()
{
	IngameCheck;
	noCDChecker.restore();
	Memory::write<unsigned char>(Client::hWorld + (Offsets::getOffset(Of_NoCD) ^ Client::_XorKey) + 0, 0x84);
	Memory::write<unsigned char>(Client::hWorld + (Offsets::getOffset(Of_NoCD) ^ Client::_XorKey) + 1, 0xC0);
}


