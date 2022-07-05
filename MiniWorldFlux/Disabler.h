#pragma once

#include "AbstractModule.h"
#include "EventManager.h"
#include "Utility.h"
#include "ImGuiHeader.h"
#include "Game.h"
#include "ProtectDestroyer.h"

class Disabler : public AbstractModule {

public:

	static Disabler* getInstance();

	void onEnabled();
	void onDisabled();

private:

	bool bypassed = false;
	Memory::ProtectDestroyer enumWndProtect;
	Memory::ProtectDestroyer enumProcProtect;
	const unsigned char bypassAsm[5] = { 0x31, 0xC0, 0xC2, 0x08, 0x00 };
	const unsigned char enumWndAsm[5] = { 0x8B, 0xFF, 0x55, 0x8B, 0xEC };
	const unsigned char enumProcAsm[5] = { 0x6A, 0x1C, 0x68, 0x48, 0x1D };

	Disabler();
	DefaultDeconstructor(Disabler);
	NoMoveConstructor(Disabler);
	NoCopyConstructor(Disabler);
	NoAssignOperator(Disabler);

};

