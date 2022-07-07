#include "pch.h"
#include "Renderer.h"

// ImGui窗口处理函数
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Renderer {

	// 全局变量
	WNDPROC originalWndProc = nullptr;      // 游戏本身的窗口处理函数

	// Hooks
	InlineHook* resetHook = nullptr;
	InlineHook* presentHook = nullptr;
	InlineHook* dipHook = nullptr;

	// Textures
	IDirect3DTexture9* playerOverlayTex = nullptr;

	void initImGui(HWND hwnd, IDirect3DDevice9* device) {
		
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();

		// 不生成配置文件
		io.IniFilename = nullptr;
		io.LogFilename = nullptr;
		io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

		// 主题
		ImGui::StyleColorsLight();

		// 字体
		Client::fluxFont = io.Fonts->AddFontFromMemoryTTF((void*)FluxFont_data, FluxFont_size, 40);
		Client::fluxIcon = io.Fonts->AddFontFromMemoryTTF((void*)FluxIconFont_data, FluxIconFont_size, 40);
		char* buffer = new char[1024];
		SHGetSpecialFolderPathA(nullptr, buffer, CSIDL_FONTS, false);
		strcat(buffer, "\\msyh.ttc");
		Client::chinese = io.Fonts->AddFontFromFileTTF(buffer, 30, nullptr, io.Fonts->GetGlyphRangesChineseFull());
		delete[] buffer;

		ImGui_ImplWin32_Init(hwnd);
		ImGui_ImplDX9_Init(device);
	}

	bool hookDx9(HWND hwnd) {

		// 创建D3D
		IDirect3D9* direct3D9 = Direct3DCreate9(D3D_SDK_VERSION);
		if (direct3D9 == nullptr) {
			LOG(L"Renderer.cpp", L"Direct3DCreate9 failed.", ERROR);
			NotificationManager::getInstance().notify("Fatal Error in D3D!", NotiLevel::ERR, 3);
			return false;
		}

		D3DPRESENT_PARAMETERS info;
		memset(&info, 0, sizeof(info));
		info.Windowed = true;
		info.SwapEffect = D3DSWAPEFFECT_COPY;

		// 创建设备，为了拿函数地址并Hook
		IDirect3DDevice9* direct3DDevice9 = nullptr;
		direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &info, &direct3DDevice9);
		if (direct3DDevice9 == nullptr) {
			LOG(L"Renderer.cpp", L"CreateDevice failed.", ERROR);
			NotificationManager::getInstance().notify("Fatal Error in D3D!", NotiLevel::ERR, 3);
			return false;
		}

		// Hook Direct3D
		DWORD* direct3DDeviceTable = (DWORD*)*(DWORD*)direct3DDevice9;
		resetHook = new InlineHook(direct3DDeviceTable[16], reinterpret_cast<DWORD> (Hook_Reset));
		presentHook = new InlineHook(direct3DDeviceTable[17], reinterpret_cast<DWORD> (Hook_Present));
		dipHook = new InlineHook(direct3DDeviceTable[82], reinterpret_cast<DWORD> (Hook_DrawIndexedPrimitive));
		LOGGER << Logger::format(L"IDirect3DDevice9::Reset: %X", L"Renderer.cpp", LogRank::DEBUG, direct3DDeviceTable[16]);
		LOGGER << Logger::format(L"IDirect3DDevice9::Present: %X", L"Renderer.cpp", LogRank::DEBUG, direct3DDeviceTable[17]);
		LOGGER << Logger::format(L"IDirect3DDevice9::DrawIndexedPrimited: %X", L"Renderer.cpp", LogRank::DEBUG, direct3DDeviceTable[82]);
		resetHook->MotifyASM();
		presentHook->MotifyASM();
		dipHook->MotifyASM();

		// 销毁设备，因为拿到地址了
		direct3D9->Release();
		direct3DDevice9->Release();

		return true;

	}

	HRESULT createTexture(IDirect3DDevice9* pDevice, IDirect3DTexture9** ppD3Dtex, DWORD colour32) {
		if (FAILED(pDevice->CreateTexture(8, 8, 1, 0, D3DFMT_A4R4G4B4, D3DPOOL_MANAGED, ppD3Dtex, NULL))) return D3D_FAILED;

		WORD  colour16 = ((WORD)((colour32 >> 28) & 0xf) << 12)
			| (WORD)(((colour32 >> 20) & 0xf) << 8)
			| (WORD)(((colour32 >> 12) & 0xf) << 4)
			| (WORD)(((colour32 >> 4) & 0xf) << 0);

		D3DLOCKED_RECT lockData;
		(*ppD3Dtex)->LockRect(0, &lockData, 0, 0);
		WORD* pDst16 = (WORD*)lockData.pBits;
		for (int i = 0; i < 8 * 8; i++) pDst16[i] = colour16;
		(*ppD3Dtex)->UnlockRect(0);
		return S_OK;
	}

	void recolorTexture(IDirect3DTexture9** ppD3Dtex, DWORD colour32) {
		
		WORD  colour16 = ((WORD)((colour32 >> 28) & 0xf) << 12)
			| (WORD)(((colour32 >> 20) & 0xf) << 8)
			| (WORD)(((colour32 >> 12) & 0xf) << 4)
			| (WORD)(((colour32 >> 4) & 0xf) << 0);

		D3DLOCKED_RECT lockData;
		(*ppD3Dtex)->LockRect(0, &lockData, 0, 0);
		WORD* pDst16 = (WORD*)lockData.pBits;
		for (int i = 0; i < 8 * 8; i++) pDst16[i] = colour16;
		(*ppD3Dtex)->UnlockRect(0);

	}

	bool startRenderer(HWND hwnd) {

		bool res = true;

		res = hookDx9(hwnd);

		return res;
	}

	// Simple helper function to load an image into a DX9 texture with common settings
	bool loadTextureFromFile(IDirect3DDevice9* device, const char* filename, Picture* pic) {

		// Load texture from disk
		PDIRECT3DTEXTURE9 texture;
		HRESULT hr = D3DXCreateTextureFromFileA(device, filename, &texture);
		if (hr != S_OK)
			return false;

		// Retrieve description of the texture surface so we can access its size
		D3DSURFACE_DESC my_image_desc;
		texture->GetLevelDesc(0, &my_image_desc);
		pic->texture = texture;
		pic->width = (int)my_image_desc.Width;
		pic->height = (int)my_image_desc.Height;

		return true;
	}

	bool isBlockHovered(Block* block) {

		return Client::rendererIO->MousePos.x >= block->x &&
			Client::rendererIO->MousePos.y >= block->y &&
			Client::rendererIO->MousePos.x <= (block->x + block->width) &&
			Client::rendererIO->MousePos.y <= (block->y + block->height);
	}

	void drawBlockBoundingBox(Block* block) {
		ImGui::GetForegroundDrawList()->AddRect(ImVec2(block->x, block->y), ImVec2(block->x + block->width, block->y + block->height), IM_COL32(255, 0, 0, 230));
	}

	bool isBlockClicked(Block* block) {
		if (isBlockHovered(block)) {
			return ImGui::IsMouseClicked(0);
		}
		return false;
	}

	bool isBlockInAnotherBlock(Block* subBlock, Block* superBlock) {

		int x1 = subBlock->x + subBlock->width;
		int y1 = subBlock->y + subBlock->height;

		return subBlock->x >= superBlock->x &&
			subBlock->y >= superBlock->y &&
			subBlock->x <= (superBlock->x + superBlock->width) &&
			subBlock->y <= (superBlock->y + superBlock->height) &&
			x1 >= superBlock->x &&
			y1 >= superBlock->y &&
			x1 <= (superBlock->x + superBlock->width) &&
			y1 <= (superBlock->y + superBlock->height);


	}

	bool isBlockDragging(Block* block, float threshold) {
		if (Renderer::isBlockHovered(block) && ImGui::IsMouseDragging(ImGuiMouseButton_Left, threshold))
			return true;
		return false;
	}

	bool isBlockRightClicked(Block* block) {
		if (isBlockHovered(block)) {
			return ImGui::IsMouseClicked(ImGuiMouseButton_Right);
		}
		return false;
	}

	bool isBlockMiddleClicked(Block* block) {
		if (isBlockHovered(block)) {
			return ImGui::IsMouseClicked(ImGuiMouseButton_Middle);
		}
		return false;
	}

	// Hooked function implements
	HRESULT WINAPI Hook_Reset(IDirect3DDevice9* direct3DDevice9, D3DPRESENT_PARAMETERS* pPresentationParameters) {

		resetHook->ResetASM();

		// 废除设备对象
		ImGui_ImplDX9_InvalidateDeviceObjects();

		HRESULT res = direct3DDevice9->Reset(pPresentationParameters);

		// 重新创建设备对象
		ImGui_ImplDX9_CreateDeviceObjects();

		resetHook->MotifyASM();

		return res;
	}

	HRESULT WINAPI Hook_Present(IDirect3DDevice9* direct3DDevice9, RECT* pSourceRect, RECT* pDestRect, HWND hDestWindowOverride, RGNDATA* pDirtyRegion) {

		presentHook->ResetASM();

		static bool called = false;
		if (!called) {

			called = true;

			// 初始化ImGui
			initImGui(Client::wndGame, direct3DDevice9);

			// 接管窗口消息
			Renderer::originalWndProc = reinterpret_cast<WNDPROC> (SetWindowLongA(Client::wndGame, GWL_WNDPROC, reinterpret_cast<long> (SelfWndProc)));

			// 初始化RendererIO
			Client::rendererIO = &(ImGui::GetIO());

			// 生成上色纹理
			Renderer::createTexture(direct3DDevice9, &Renderer::playerOverlayTex, D3DCOLOR_RGBA(250, 0, 0, 230));

		}

		// 绘制
		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		EventManager::getInstance().call(Events::EventKeyDown);
		EventManager::getInstance().call(Events::EventUpdateData);
		EventManager::getInstance().call(Events::EventRenderOverlay);

		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

		HRESULT res = direct3DDevice9->Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);

		presentHook->MotifyASM();

		// 调用原来的
		return res;
	}

	HRESULT WINAPI Hook_DrawIndexedPrimitive(IDirect3DDevice9* direct3DDevice9, D3DPRIMITIVETYPE type, INT baseVertexIndex, UINT minVertexIndex, UINT numVertices, UINT startIndex, UINT primCount) {
		
		HRESULT res = D3D_OK;
		dipHook->ResetASM();

		IDirect3DVertexBuffer9* vertexBuffer = nullptr;
		uint32_t offset = 0;
		uint32_t stride = 0;
		if (SUCCEEDED(direct3DDevice9->GetStreamSource(0U, &vertexBuffer, &offset, &stride)))
			vertexBuffer->Release();
		
		Shader* shaderMod = Shader::getInstance();
		if ((stride == 48 || stride == 40) && shaderMod->getToggle()) {

			if (shaderMod->colorMode()) {
				Renderer::recolorTexture(&Renderer::playerOverlayTex, shaderMod->getColor());
				direct3DDevice9->SetTexture(0, Renderer::playerOverlayTex);
			}

			if (shaderMod->wireframeMode())
				direct3DDevice9->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

			if (shaderMod->disaledZBuffer())
				direct3DDevice9->SetRenderState(D3DRS_ZENABLE, FALSE);

			res = direct3DDevice9->DrawIndexedPrimitive(type, baseVertexIndex, minVertexIndex, numVertices, startIndex, primCount);
			
			if (shaderMod->disaledZBuffer())
				direct3DDevice9->SetRenderState(D3DRS_ZENABLE, TRUE);

			if (shaderMod->wireframeMode())
				direct3DDevice9->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

		}
		else {

			res = direct3DDevice9->DrawIndexedPrimitive(type, baseVertexIndex, minVertexIndex, numVertices, startIndex, primCount);
		
		}
		
		dipHook->MotifyASM();
		return res;
	}

	LRESULT CALLBACK SelfWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

		if (uMsg == WM_KEYDOWN) {

			if (ClickGui::getInstance()->bindingKey) {

				ClickGui::getInstance()->bindingModule->setKey(static_cast<unsigned char>(wParam));
				ClickGui::getInstance()->endBindKey();
			}
			else {

				Client::handleModuleKeyEvent(static_cast<unsigned char>(wParam));
			}

		}

		// ImGui接管窗口处理
		if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) return true;

		if (ClickGui::getInstance()->getToggle()
			&& (uMsg == WM_LBUTTONDOWN
				|| uMsg == WM_LBUTTONUP
				|| uMsg == WM_LBUTTONDBLCLK
				|| uMsg == WM_MBUTTONDOWN
				|| uMsg == WM_MBUTTONUP
				|| uMsg == WM_MBUTTONDBLCLK
				|| uMsg == WM_RBUTTONDOWN
				|| uMsg == WM_RBUTTONUP
				|| uMsg == WM_RBUTTONDBLCLK)) return true;

		// 调用原先的窗口处理
		return CallWindowProcA(Renderer::originalWndProc, hWnd, uMsg, wParam, lParam);
	}

}
