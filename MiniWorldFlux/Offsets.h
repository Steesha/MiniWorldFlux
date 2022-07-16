#pragma once
#include "pch.h"
/* 在这里更换全局XORKEY */
#define g_XORKEY 1932092807
constexpr unsigned int Of_FakePosition = 0;
constexpr unsigned int Of_Reach = 1;
constexpr unsigned int Of_NoFall = 2;
constexpr unsigned int Of_Phase = 3;
constexpr unsigned int Of_World = 4;
constexpr unsigned int Of_UIRenderer = 5;
constexpr unsigned int Of_FPSBase = 6;
constexpr unsigned int Of_FPS_1 = 7;
constexpr unsigned int Of_Ping = 8;
constexpr unsigned int Of_NoSpread = 9;
constexpr unsigned int Of_NoRecoil = 10;
constexpr unsigned int Of_IsPlaying = 11;
constexpr unsigned int Of_PlayerInfoBase = 12;
constexpr unsigned int Of_MpGameSurvive = 13;
constexpr unsigned int Of_RoomManager = 14;
constexpr unsigned int Of_GameVersion = 15;
constexpr unsigned int Of_MagicBullet = 16;
constexpr unsigned int Of_MagicBulletRetn = 17;
constexpr unsigned int Of_FakeMessenger_System = 18;
constexpr unsigned int Of_FakeMessenger_System_Retn = 19;
constexpr unsigned int Of_FakeMessenger_Player = 20;
constexpr unsigned int Of_FakeMessenger_Player_Retn = 21;
constexpr unsigned int Of_Velocity = 22;
constexpr unsigned int Of_Velocity_Retn = 23;
constexpr unsigned int Of_Velocity_MemoryCode = 24;
constexpr unsigned int Of_NoCD = 25;

namespace Offsets {
	
	static unsigned long getOffset(int cate) {
		VM_DOLPHIN_RED_START

		// Module
		unsigned long FakePosition = 0x110AF9C ^ g_XORKEY;
		unsigned long Reach = 0x1056DB3 ^ g_XORKEY;
		unsigned long NoFall = 0x8ED7B7 ^ g_XORKEY;
		unsigned long Phase = 0x8ED24A ^ g_XORKEY;
		unsigned long NoSpread = 0x10B9B24 ^ g_XORKEY;
		unsigned long NoRecoil = 0x10B9B63 ^ g_XORKEY;
		unsigned long MagicBullet = 0xC285D7 ^ g_XORKEY;
		unsigned long MagicBulletRetn = 0xC285DD ^ g_XORKEY;
		unsigned long FakeMessenger_System = 0xD7FA3F ^ g_XORKEY;
		unsigned long FakeMessenger_System_Retn = 0xD7FA49 ^ g_XORKEY;
		unsigned long FakeMessenger_Player = 0x80C2A6 ^ g_XORKEY;
		unsigned long FakeMessenger_Player_Retn = 0x80C2AD ^ g_XORKEY;
		unsigned long Velocity = 0x92A24F ^ g_XORKEY;
		unsigned long Velocity_Retn = 0x92A255 ^ g_XORKEY;
		unsigned long Velocity_MemoryCode = 0x118A6AE ^ g_XORKEY;
		unsigned long NoCD = 0x183BBDE ^ g_XORKEY;

		// World
		unsigned long World = 0x1EBD72C ^ g_XORKEY;

		// Matrix
		unsigned long UIRenderer = 0x1E5E268 ^ g_XORKEY;

		// RoomManager
		unsigned long RoomManager = 0x1E5E354 ^ g_XORKEY;
		unsigned long GameVersion = 0x1E5E378 ^ g_XORKEY;

		// Misc
		unsigned long FPSBase = 0x1E5E288 ^ g_XORKEY;
		unsigned long FPS_1 = 0x80 ^ g_XORKEY;
		unsigned long Ping = 0x23859CC ^ g_XORKEY;
		unsigned long IsPlaying = 0x23CF230 ^ g_XORKEY;

		// Player Info
		unsigned long PlayerInfoBase = 0x238348C ^ g_XORKEY;
		unsigned long MpGameSurvive = 0x40 ^ g_XORKEY;

		unsigned long result = 0;

		// 访问次数多的放前面
		if (cate == Of_World) result = World;
		if (cate == Of_UIRenderer) result = UIRenderer;
		if (cate == Of_FPSBase) result = FPSBase;
		if (cate == Of_FPS_1) result = FPS_1;
		if (cate == Of_Ping) result = Ping;
		if (cate == Of_FakePosition) result = FakePosition;
		if (cate == Of_Reach) result = Reach;
		if (cate == Of_NoFall) result = NoFall;
		if (cate == Of_Phase) result = Phase;
		if (cate == Of_NoSpread) result = NoSpread;
		if (cate == Of_NoRecoil) result = NoRecoil;
		if (cate == Of_IsPlaying) result = IsPlaying;
		if (cate == Of_PlayerInfoBase) result = PlayerInfoBase;
		if (cate == Of_MpGameSurvive) result = MpGameSurvive;
		if (cate == Of_RoomManager) result = RoomManager;
		if (cate == Of_GameVersion) result = GameVersion;
		if (cate == Of_MagicBullet) result = MagicBullet;
		if (cate == Of_MagicBulletRetn) result = MagicBulletRetn;
		if (cate == Of_FakeMessenger_System) result = FakeMessenger_System;
		if (cate == Of_FakeMessenger_System_Retn) result = FakeMessenger_System_Retn;
		if (cate == Of_FakeMessenger_Player) result = FakeMessenger_Player;
		if (cate == Of_FakeMessenger_Player_Retn) result = FakeMessenger_Player_Retn;
		if (cate == Of_Velocity) result = Velocity;
		if (cate == Of_Velocity_Retn) result = Velocity_Retn;
		if (cate == Of_Velocity_MemoryCode) result = Velocity_MemoryCode;
		if (cate == Of_NoCD) result = NoCD;
		return result;
		VM_DOLPHIN_RED_END
	}
};
