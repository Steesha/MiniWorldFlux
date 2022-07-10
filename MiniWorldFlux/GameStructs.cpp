#include "pch.h"
#include "GameStructs.h"
#include "Client.h"

namespace SDK {

	static Address hWorld = reinterpret_cast<Address>(GetModuleHandleA("libiworld_micro.dll"));

	World* getWorld() {

		Address* ppWorld = reinterpret_cast<Address*>(hWorld + Offsets::getOffset(Of_World) ^ Client::_XorKey);
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
		
		Address* pUIRenderer = reinterpret_cast<Address*>(hWorld + Offsets::getOffset(Of_UIRenderer) ^ Client::_XorKey);
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
		
		Address* pRoomManager = reinterpret_cast<Address*>(hWorld + Offsets::getOffset(Of_RoomManager) ^ Client::_XorKey);
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
		char* szVersion = reinterpret_cast<char*>(hWorld + Offsets::getOffset(Of_GameVersion) ^ Client::_XorKey);
		if (IsBadReadPtr(szVersion, sizeof(szVersion)) == 0)		
			return std::string(szVersion);
		return std::string("");
	}

	float getIngameFPS() {

		Address* pBase = reinterpret_cast<Address*>(hWorld + Offsets::getOffset(Of_FPSBase) ^ Client::_XorKey);
		if (IsBadReadPtr(pBase, sizeof(pBase)) == 0) {
			float* pFPS = reinterpret_cast<float*>((*pBase) + Offsets::getOffset(Of_FPS_1) ^ Client::_XorKey);
			if (IsBadReadPtr(pFPS, sizeof(pFPS)) == 0) {
				return *pFPS;
			}
		}
		return -1;
	}

	int getIngamePing() {
		
		Address* pPing = reinterpret_cast<Address*>(hWorld + Offsets::getOffset(Of_Ping) ^ Client::_XorKey);
		if (IsBadReadPtr(pPing, sizeof(pPing)) == 0)
			return *pPing;
		return -1;
	}

}
