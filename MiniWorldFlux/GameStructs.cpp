#include "pch.h"
#include "GameStructs.h"

namespace SDK {

	static Address hWorld = reinterpret_cast<Address>(GetModuleHandleA("libiworld_micro.dll"));

	World* getWorld() {

		Address* ppWorld = reinterpret_cast<Address*>(hWorld + Offsets::getOffset(Of_World));
		if (IsBadReadPtr(ppWorld, sizeof(ppWorld)) == 0) {
			
			World* pWorld = reinterpret_cast<World*>(*ppWorld);
			if (IsBadReadPtr(pWorld, sizeof(pWorld)) == 0)
				return pWorld;
			else
				return nullptr;

		}
		
		return nullptr;
	}

	UIRenderer* getUIRenderer() {
		
		Address* pUIRenderer = reinterpret_cast<Address*>(hWorld + Offsets::getOffset(Of_UIRenderer));
		if (IsBadReadPtr(pUIRenderer, sizeof(pUIRenderer)) == 0) {
			
			UIRenderer* renderer = reinterpret_cast<UIRenderer*>(*pUIRenderer);
			if (IsBadReadPtr(renderer, sizeof(renderer)) == 0)
				return renderer;
			else
				return nullptr;

		}
		
		return nullptr;
	}

	float getIngameFPS() {

		Address* pBase = reinterpret_cast<Address*>(hWorld + Offsets::getOffset(Of_FPSBase));
		if (IsBadReadPtr(pBase, sizeof(pBase)) == 0) {
			float* pFPS = reinterpret_cast<float*>((*pBase) + Offsets::getOffset(Of_FPS_1));
			if (IsBadReadPtr(pFPS, sizeof(pFPS)) == 0) {
				return *pFPS;
			}
		}
		return -1;
	}

	int getIngamePing() {
		
		Address* pPing = reinterpret_cast<Address*>(hWorld + Offsets::getOffset(Of_Ping));
		if (IsBadReadPtr(pPing, sizeof(pPing)) == 0)
			return *pPing;
		return -1;
	}

}
