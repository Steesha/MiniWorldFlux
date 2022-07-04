#pragma once
#include <Windows.h>

namespace Simulator {
	
	constexpr unsigned char KEY_NONE = 0xFF;
	constexpr unsigned char KEY_A = 0x41;
	constexpr unsigned char KEY_B = 0x42;
	constexpr unsigned char KEY_C = 0x43;
	constexpr unsigned char KEY_D = 0x44;
	constexpr unsigned char KEY_E = 0x45;
	constexpr unsigned char KEY_F = 0x46;
	constexpr unsigned char KEY_G = 0x47;
	constexpr unsigned char KEY_H = 0x48;
	constexpr unsigned char KEY_I = 0x49;
	constexpr unsigned char KEY_J = 0x4A;
	constexpr unsigned char KEY_K = 0x4B;
	constexpr unsigned char KEY_L = 0x4C;
	constexpr unsigned char KEY_M = 0x4D;
	constexpr unsigned char KEY_N = 0x4E;
	constexpr unsigned char KEY_O = 0x4F;
	constexpr unsigned char KEY_P = 0x50;
	constexpr unsigned char KEY_Q = 0x51;
	constexpr unsigned char KEY_R = 0x52;
	constexpr unsigned char KEY_S = 0x53;
	constexpr unsigned char KEY_T = 0x54;
	constexpr unsigned char KEY_U = 0x55;
	constexpr unsigned char KEY_V = 0x56;
	constexpr unsigned char KEY_W = 0x57;
	constexpr unsigned char KEY_X = 0x58;
	constexpr unsigned char KEY_Y = 0x59;
	constexpr unsigned char KEY_Z = 0x5A;

	void kpress(unsigned char vKey);
	void kpress(unsigned char vKey, long time);

}
