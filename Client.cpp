#include "Client.h"

namespace Client {

	// Globals
	HWND wndGame = nullptr;						// ��Ϸ���ھ��
	HMODULE clientModule = nullptr;				// DLL���
	std::string clientName("Flux");				// ����
	std::string clientAuthor("����Ayin");		// ������
	std::string clientMajorVersion("0");		// ���汾��
	std::string clientMinorVersion("1");		// ���汾��
	std::string clientDllPath("");				// �ͻ���DLL·��
	std::string clientAssetsPath("");			// �ͻ�����Դ·��
	ImGuiIO* rendererIO = nullptr;				// ImGuiIO
	ImFont* fluxFont = nullptr;					// Flux����
	ImFont* fluxIcon = nullptr;					// Fluxͼ��
	ImFont* chinese = nullptr;					// ˼Դ����
	Address hWorld = 0;							// libiworld_micro.dll��ַ

	void initClient() {

		// ��ȡ��Ϸ���ھ��
		Client::wndGame = FindWindowA("RenderWindow_ClassName", nullptr);

		// ��ȡ��ģ���ַ
		Client::hWorld = reinterpret_cast<Address>(GetModuleHandleA("libiworld_micro.dll"));
	
		// ��ȡDLL·������Դ·��
		char path[1024];
		RtlZeroMemory(path, 1024);
		GetModuleFileNameA(Client::clientModule, path, 1024);
		Client::clientDllPath = std::string(path);
		(strrchr(path, '\\'))[1] = 0;
		Client::clientAssetsPath = std::string(strcat(path, "assets\\"));

		g_localPlayer = Client::hWorld + Offsets::LocalPlayer;
		g_freeItemsCallAddr = hWorld + Offsets::FreeItemsCall;

	}

	void initModules() {
		
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
		ModuleManager::getInstance().addModule<FreeItems>(FreeItems::getInstance());

	}

	void initEvents() {
		
		EventManager::getInstance().reg(Events::EventKeyDown, handleKeyEvent);
		EventManager::getInstance().reg(Events::EventUpdateData, Game::updateData);

	}

	void loadConfig() {
		
		Disabler::getInstance()->enable();
		HUD::getInstance()->enable();
		IDProtection::getInstance()->enable();
		Team::getInstance()->enable();

		FakePosition::getInstance()->setKey(Simulator::KEY_F);
		Phase::getInstance()->setKey(Simulator::KEY_F);
		AirJump::getInstance()->setKey(Simulator::KEY_V);
		AutoClicker::getInstance()->setKey(Simulator::KEY_E);
		Reach::getInstance()->setKey(Simulator::KEY_E);

	}

	void startClient(HMODULE thisModule) {

		Client::clientModule = thisModule;

#ifdef _DEBUG
		Utility::openConsole();
#endif

		Client::initClient();
		Client::initModules();
		Client::initEvents();
		Renderer::startRenderer(Client::wndGame);
		Client::loadConfig();

	}

	void handleKeyEvent() {

		static bool opening = false;

		if (ImGui::IsKeyDown(ImGuiKey_RightShift)) {
			if (!opening) {
				EventManager::getInstance().call(Events::EventOpenClickGui);
				opening = true;
			}
		}

		if (ImGui::IsKeyDown(ImGuiKey_Escape)) {
			if (opening) {
				EventManager::getInstance().call(Events::EventCloseClickGui);
				opening = false;
			}
		}
	}

	void handleModuleKeyEvent(unsigned char keyCode) {
		
		for (HMOD m : ModuleManager::getInstance().getModules()) {
			AbstractModule* mod = ToBaseModule(m);

			if (mod->getKey() == Simulator::KEY_NONE) continue;
			if (mod->getKey() == keyCode) mod->toggle();

		}
	}

	void loadTextures(IDirect3DDevice9* device) {


	}

}