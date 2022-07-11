#pragma once
#include "pch.h"
#include "InlineHook.h"
#include "Client.h"
#include "EventManager.h"

#define D3D_FAILED 0x857

struct Block {

	float x;
	float y;
	float width;
	float height;
};

namespace Renderer {

	// 全局变量
	extern WNDPROC originalWndProc;      // 游戏本身的窗口处理函数

	// Hooks
	extern InlineHook* resetHook;
	extern InlineHook* presentHook;
	extern InlineHook* dipHook;

	// Textures
	extern IDirect3DTexture9* playerOverlayTex;

	void initImGui(HWND hwnd, IDirect3DDevice9* device);

	bool hookDx9(HWND hwnd);
	
	bool startRenderer(HWND hwnd);

	HRESULT createTexture(IDirect3DDevice9* pDevice, IDirect3DTexture9** ppD3Dtex, DWORD colour32);

	void recolorTexture(IDirect3DTexture9** ppD3Dtex, DWORD colour32);

	bool isBlockHovered(Block* block);

	void drawBlockBoundingBox(Block* block);

	bool isBlockClicked(Block* block);

	bool isBlockInAnotherBlock(Block* subBlock, Block* superBlock);

	bool isBlockDragging(Block* block, float threshold = -1.0f);

	bool isBlockRightClicked(Block* block);

	bool isBlockMiddleClicked(Block* block);

	// 自己的窗口处理函数
	LRESULT CALLBACK SelfWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	// Hooked functions
	HRESULT WINAPI Hook_Reset(IDirect3DDevice9* direct3DDevice9, D3DPRESENT_PARAMETERS* pPresentationParameters);
	HRESULT WINAPI Hook_Present(IDirect3DDevice9* direct3DDevice9, RECT* pSourceRect, RECT* pDestRect, HWND hDestWindowOverride, RGNDATA* pDirtyRegion);
	HRESULT WINAPI Hook_DrawIndexedPrimitive(IDirect3DDevice9* direct3DDevice9, D3DPRIMITIVETYPE type, INT baseVertexIndex, UINT minVertexIndex, UINT numVertices, UINT startIndex, UINT primCount);

}

