#pragma once
#include <Windows.h>

constexpr int CODE_LENGTH = 5;

class InlineHook {

private:

	// 原始指令大小
	BYTE s_originalBytes[CODE_LENGTH];

	// 自己构造的汇编指令
	BYTE s_newBytes[CODE_LENGTH];

	// 原始函数地址
	DWORD s_originalAddress;

	// 自己的函数地址
	DWORD s_newAddress;

	DWORD ModifyMemoryAttributes(DWORD address, DWORD attributes = PAGE_EXECUTE_READWRITE);

public:

	InlineHook(DWORD originalFuncAddr, DWORD newFuncAddr);

	VOID MotifyASM();

	VOID ResetASM();
};
