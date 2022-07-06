#pragma once
#include <ThemidaSDK\ThemidaSDK.h>
#include <Windows.h>
#include "Utility.h"
#include "Renderer.h"
#include "ImGuiHeader.h"
#include "EventManager.h"
#include "ModuleManager.h"
#include "Logger.h"

// Modules
#include "ClickGui.h"
#include "IDProtection.h"
#include "HighJump.h"
#include "FasterSpeed.h"
#include "ESP.h"
#include "HUD.h"
#include "AirJump.h"
#include "Fly.h"
#include "Aimbot.h"
#include "FakePosition.h"
#include "Disabler.h"
#include "Phase.h"
#include "Reach.h"
#include "BoxESP.h"
#include "AutoClicker.h"
#include "Team.h"
#include "Radar.h"
#include "NoFall.h"
#include "TargetHUD.h"
#include "NoRecoil.h"

#define MakeDisposableThread(_Executor, _Param) CloseHandle(CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(_Executor), _Param, 0, nullptr))

namespace Client {

	extern HWND wndGame;
	extern HMODULE clientModule;
	extern std::string clientAuthor;
	extern std::string clientMajorVersion;
	extern std::string clientMinorVersion;
	extern std::string clientDllPath;
	extern ImGuiIO* rendererIO;
	extern ImFont* fluxFont;
	extern ImFont* fluxIcon;
	extern ImFont* chinese;
	extern Address hWorld;

	void initClient();
	void initModules();
	void initEvents();
	void startClient(HMODULE thisModule);
	void handleGuiEvent();
	void handleModuleKeyEvent(unsigned char keyCode);
	void loadConfig();

}

