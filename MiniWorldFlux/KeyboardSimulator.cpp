#include "pch.h"
#include "KeyboardSimulator.h"

unsigned char scan_code(DWORD pKey) {
	const DWORD result = MapVirtualKeyW(pKey, MAPVK_VK_TO_VSC);
	return static_cast<unsigned char>(result);
}

void press_key(unsigned char pKey) {
	keybd_event(pKey, scan_code(pKey), 0, 0);
}

void release_key(unsigned char pKey) {
	keybd_event(pKey, scan_code(pKey), KEYEVENTF_KEYUP, 0);
}

namespace Simulator {
	
	void kpress(unsigned char vKey) {
		
		press_key(vKey);
		release_key(vKey);
	}

	void kpress(unsigned char vKey, long time) {

		// keybd_event(vKey, 0, 0, 0);
		press_key(vKey);
		Sleep(time);
		// keybd_event(vKey, 0, KEYEVENTF_KEYUP, 0);
		release_key(vKey);
	}

}
