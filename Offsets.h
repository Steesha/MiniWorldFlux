#pragma once

namespace Offsets {

	// Module
	constexpr unsigned long FakePosition = 0x10EF2C2;
	constexpr unsigned long FlyCheck = 0x10FD66B;
	constexpr unsigned long Reach = 0x104E453;
	constexpr unsigned long NoFall = 0x8E8027;

	// World
	constexpr unsigned long World = 0x1EB45E4;

	// Matrix
	constexpr unsigned long UIRenderer = 0x1E55168;

	// Misc
	constexpr unsigned long FPSBase = 0x1E55188;
	constexpr unsigned long FPS_1 = 0x80;
	constexpr unsigned long Ping = 0x237C83C;
	constexpr unsigned long NoSpread = 0x10B0F04;
	constexpr unsigned long NoRecoil = 0x10B0F43;
	constexpr unsigned long FreeItemsCall = 0x10ED1B0;	// Deprecated
	constexpr unsigned long LocalPlayer = 0x235F5A8;	// Deprecated

	// Player Info
	constexpr unsigned long PlayerInfoBase = 0x237A314;
	constexpr unsigned long MpGameSurvive = 0x40;

};
