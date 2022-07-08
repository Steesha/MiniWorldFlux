#pragma once
#define Of_FakePosition 0
#define Of_Reach 1
#define Of_NoFall 2
#define Of_Phase 3
#define Of_World 4
#define Of_UIRenderer 5
#define Of_FPSBase 6
#define Of_FPS_1 7
#define Of_Ping 8
#define Of_NoSpread 9
#define Of_NoRecoil 10
#define Of_IsPlaying 11
#define Of_PlayerInfoBase 12
#define Of_MpGameSurvive 13
namespace Offsets {
	static unsigned long getOffset(int cate)
	{
		// Module
		unsigned long FakePosition = 0x110AF9C;
		unsigned long Reach = 0x1056DB3;
		unsigned long NoFall = 0x8ED7B7;
		unsigned long Phase = 0x8ED24A;

		// World
		unsigned long World = 0x1EBD72C;

		// Matrix
		unsigned long UIRenderer = 0x1E5E268;

		// Misc
		unsigned long FPSBase = 0x1E5E288;
		unsigned long FPS_1 = 0x80;
		unsigned long Ping = 0x23859CC;
		unsigned long NoSpread = 0x10B9B24;
		unsigned long NoRecoil = 0x10B9B63;
		unsigned long IsPlaying = 0x23CF230;

		// Player Info
		unsigned long PlayerInfoBase = 0x238348C;
		unsigned long MpGameSurvive = 0x40;

		if (cate == Of_FakePosition) return FakePosition;
		if (cate == Of_Reach) return Reach;
		if (cate == Of_NoFall) return NoFall;
		if (cate == Of_Phase) return Phase;
		if (cate == Of_World) return World;
		if (cate == Of_UIRenderer) return UIRenderer;
		if (cate == Of_FPSBase) return FPSBase;
		if (cate == Of_FPS_1) return FPS_1;
		if (cate == Of_Ping) return Ping;
		if (cate == Of_NoSpread) return NoSpread;
		if (cate == Of_NoRecoil) return NoRecoil;
		if (cate == Of_IsPlaying) return IsPlaying;
		if (cate == Of_PlayerInfoBase) return PlayerInfoBase;
		if (cate == Of_MpGameSurvive) return MpGameSurvive;

		return -1;
	}
};
