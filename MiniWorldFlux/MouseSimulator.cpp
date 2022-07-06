#include "pch.h"
#include "MouseSimulator.h"

namespace Simulator {

	void mexecutor(long* time) {

		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
		if (IsBadReadPtr(time, sizeof(time) == 0))
			Sleep(*time);
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

	}

	void mlclick() {
		CloseHandle(CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(mexecutor), nullptr, 0, nullptr));
	}

	void mlclick(long time) {

		long* param = new long(time);
		CloseHandle(CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(mexecutor), param, 0, nullptr));
		delete param;
	}

}
