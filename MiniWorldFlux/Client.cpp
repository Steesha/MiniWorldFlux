#include "pch.h"
#include "Client.h"
#include "ClientLogin.h"

namespace Client {

	// Globals
	HWND wndGame = nullptr;						// 游戏窗口句柄
	HMODULE clientModule = nullptr;				// DLL句柄
	std::string clientName("Flux");				// 端名
	std::string clientAuthor("阿茵Ayin");		// 作者名
	std::string clientMajorVersion("0");		// 主版本号
	std::string clientMinorVersion("1");		// 副版本号
	std::string clientDllPath("");				// 客户端DLL路径
	std::string clientAssetsPath("");			// 客户端资源路径
	ImGuiIO* rendererIO = nullptr;				// ImGuiIO
	ImFont* fluxFont = nullptr;					// Flux字体
	ImFont* fluxIcon = nullptr;					// Flux图标
	ImFont* chinese = nullptr;					// 微软雅黑
	Address hWorld = 0;							// libiworld_micro.dll基址
	std::string gameVersion("");				// 游戏版本
	DWORD _XorKey = 0;                          // xorKEY

	void initClient() {
		VM_LION_WHITE_START

		// 获取游戏窗口句柄
		Client::wndGame = FindWindow(L"RenderWindow_ClassName", nullptr);

		// 获取主模块基址
		Client::hWorld = reinterpret_cast<Address>(GetModuleHandle(L"libiworld_micro.dll"));

		// 获取游戏版本
		Client::gameVersion = SDK::getGameVersion();

		Message msg = Logger::format(L"libiworld_micro BaseAddr: %X", L"Client.cpp", LogRank::DEBUG, hWorld);
		LOGGER << msg;

		VM_LION_WHITE_END
	}

	void initModules() {
		VM_LION_WHITE_START
		ModuleManager::getInstance().addModule<ClickGui>(ClickGui::getInstance());
		ModuleManager::getInstance().addModule<Disabler>(Disabler::getInstance());
		ModuleManager::getInstance().addModule<IDProtection>(IDProtection::getInstance());
		ModuleManager::getInstance().addModule<HighJump>(HighJump::getInstance());
		ModuleManager::getInstance().addModule<FasterSpeed>(FasterSpeed::getInstance());
		ModuleManager::getInstance().addModule<ESP>(ESP::getInstance());
		ModuleManager::getInstance().addModule<HUD>(HUD::getInstance());
		ModuleManager::getInstance().addModule<AirJump>(AirJump::getInstance());
		ModuleManager::getInstance().addModule<Fly>(Fly::getInstance());
		ModuleManager::getInstance().addModule<Aimbot>(Aimbot::getInstance());
		ModuleManager::getInstance().addModule<FakePosition>(FakePosition::getInstance());
		ModuleManager::getInstance().addModule<Phase>(Phase::getInstance());
		ModuleManager::getInstance().addModule<Reach>(Reach::getInstance());
		ModuleManager::getInstance().addModule<BoxESP>(BoxESP::getInstance());
		ModuleManager::getInstance().addModule<AutoClicker>(AutoClicker::getInstance());
		ModuleManager::getInstance().addModule<Team>(Team::getInstance());
		ModuleManager::getInstance().addModule<Radar>(Radar::getInstance());
		ModuleManager::getInstance().addModule<NoFall>(NoFall::getInstance());
		ModuleManager::getInstance().addModule<TargetHUD>(TargetHUD::getInstance());
		ModuleManager::getInstance().addModule<NoRecoil>(NoRecoil::getInstance());
		ModuleManager::getInstance().addModule<Shader>(Shader::getInstance());
		ModuleManager::getInstance().addModule<MagicBullet>(MagicBullet::getInstance());
		ModuleManager::getInstance().addModule<FakeMessager>(FakeMessager::getInstance());
		ModuleManager::getInstance().addModule<FastBullet>(FastBullet::getInstance());
		VM_LION_WHITE_END
	}

	void initEvents() {
		
		EventManager::getInstance().reg(Events::EventKeyDown, handleGuiEvent);
		EventManager::getInstance().reg(Events::EventUpdateData, Game::updateData);
#ifdef _DEBUG
		EventManager::getInstance().reg(Events::EventUpdateData, MakeHandler(&Logger::getInstance(), &Logger::flush));
#endif

	}

	void loadConfig() {
		
		Disabler::getInstance()->enable();
		HUD::getInstance()->enable();
		IDProtection::getInstance()->enable();
		Team::getInstance()->enable();

	}

	void startClient(HMODULE thisModule) {
		ClientLogin* login = new ClientLogin();
		if (!login->Login())
		{
			delete login;
			ExitProcess(-1);
			return;
		}
		_XorKey = login->getXORKEY();

		Client::clientModule = thisModule;

#ifdef _DEBUG
		Utility::openConsole();
#endif
		Client::initClient();
		Client::initModules();
		Client::initEvents();
		Renderer::startRenderer(Client::wndGame);
		Client::loadConfig();

		LOG(L"Client.cpp", L"Client started.", INFO);

	}

	void handleGuiEvent() {

		if (ImGui::IsKeyDown(ImGuiKey_RightShift))
			if (!ClickGui::getInstance()->getToggle())
				EventManager::getInstance().call(Events::EventOpenClickGui);

		if (ImGui::IsKeyDown(ImGuiKey_Escape))
			if (ClickGui::getInstance()->getToggle())
				EventManager::getInstance().call(Events::EventCloseClickGui);

	}

	void handleModuleKeyEvent(unsigned char keyCode) {
		
		for (HMOD m : ModuleManager::getInstance().getModules()) {
			AbstractModule* mod = ToBaseModule(m);

			if (mod->getKey() == Simulator::KEY_NONE) continue;
			if (mod->getKey() == keyCode) mod->toggle();

		}
	}

}
