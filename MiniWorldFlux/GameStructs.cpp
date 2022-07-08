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

	RoomManager* getRoomManager() {
		
		Address* pRoomManager = reinterpret_cast<Address*>(hWorld + Offsets::getOffset(Of_RoomManager));
		if (IsBadReadPtr(pRoomManager, sizeof(pRoomManager)) == 0) {
			
			RoomManager* roomManager = reinterpret_cast<RoomManager*>(*pRoomManager);
			if (IsBadReadPtr(roomManager, sizeof(roomManager)) == 0)
				return roomManager;
			else
				return nullptr;

		}

		return nullptr;
	}

	std::string getGameVersion() {
		char* szVersion = reinterpret_cast<char*>(hWorld + Offsets::getOffset(Of_GameVersion));
		if (IsBadReadPtr(szVersion, sizeof(szVersion)) == 0)		
			return std::string(szVersion);
		return std::string("");
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
