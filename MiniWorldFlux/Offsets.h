#pragma once

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
constexpr unsigned int Of_FakeMessager = 18;
constexpr unsigned int Of_FakeMessagerRetn = 19;

namespace Offsets {

	static unsigned long getOffset(int cate) {

		// Module
		unsigned long FakePosition = 0x110AF9C;
		unsigned long Reach = 0x1056DB3;
		unsigned long NoFall = 0x8ED7B7;
		unsigned long Phase = 0x8ED24A;
		unsigned long NoSpread = 0x10B9B24;
		unsigned long NoRecoil = 0x10B9B63;
		unsigned long MagicBullet = 0xC285D7;
		unsigned long MagicBulletRetn = 0xC285DD;
		unsigned long FakeMessager = 0xD7FA3F;
		unsigned long FakeMessagerRetn = 0xD7FA49;

		// World
		unsigned long World = 0x1EBD72C;

		// Matrix
		unsigned long UIRenderer = 0x1E5E268;

		// RoomManager
		unsigned long RoomManager = 0x1E5E354;
		unsigned long GameVersion = 0x1E5E378;

		// Misc
		unsigned long FPSBase = 0x1E5E288;
		unsigned long FPS_1 = 0x80;
		unsigned long Ping = 0x23859CC;
		unsigned long IsPlaying = 0x23CF230;

		// Player Info
		unsigned long PlayerInfoBase = 0x238348C;
		unsigned long MpGameSurvive = 0x40;

		// 访问次数多的放前面
		if (cate == Of_World) return World;
		if (cate == Of_UIRenderer) return UIRenderer;
		if (cate == Of_FPSBase) return FPSBase;
		if (cate == Of_FPS_1) return FPS_1;
		if (cate == Of_Ping) return Ping;
		if (cate == Of_FakePosition) return FakePosition;
		if (cate == Of_Reach) return Reach;
		if (cate == Of_NoFall) return NoFall;
		if (cate == Of_Phase) return Phase;
		if (cate == Of_NoSpread) return NoSpread;
		if (cate == Of_NoRecoil) return NoRecoil;
		if (cate == Of_IsPlaying) return IsPlaying;
		if (cate == Of_PlayerInfoBase) return PlayerInfoBase;
		if (cate == Of_MpGameSurvive) return MpGameSurvive;
		if (cate == Of_RoomManager) return RoomManager;
		if (cate == Of_GameVersion) return GameVersion;
		if (cate == Of_MagicBullet) return MagicBullet;
		if (cate == Of_MagicBulletRetn) return MagicBulletRetn;
		if (cate == Of_FakeMessager) return FakeMessager;
		if (cate == Of_FakeMessagerRetn) return FakeMessagerRetn;

		return -1;
	}
};
