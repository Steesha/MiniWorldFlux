#include "pch.h"
#include "InlineHook.h"

DWORD InlineHook::ModifyMemoryAttributes(DWORD address, DWORD attributes) {

	DWORD oldAttributes;
	VirtualProtect(reinterpret_cast<void*>(address), CODE_LENGTH, attributes, &oldAttributes);
	return oldAttributes;
}

InlineHook::InlineHook(DWORD originalFuncAddr, DWORD newFuncAddr) : s_originalAddress(originalFuncAddr), s_newAddress(newFuncAddr) {

	// jmp
	s_newBytes[0] = '\xE9';

	// 计算偏移
	DWORD offset = newFuncAddr - (originalFuncAddr + CODE_LENGTH);

	// 构造跳转字节数组
	memcpy(&s_newBytes[1], &offset, CODE_LENGTH - 1);

	// 修改内存属性
	DWORD oldAttributes = ModifyMemoryAttributes(originalFuncAddr);

	// 保存原始函数字节
	memcpy(s_originalBytes, reinterpret_cast<void*>(originalFuncAddr), CODE_LENGTH);

	// 恢复内存属性
	ModifyMemoryAttributes(originalFuncAddr, oldAttributes);

}

VOID InlineHook::MotifyASM() {

	DWORD oldAttributes = ModifyMemoryAttributes(s_originalAddress);

	memcpy(reinterpret_cast<void*>(s_originalAddress), s_newBytes, CODE_LENGTH);

	ModifyMemoryAttributes(s_originalAddress, oldAttributes);
}

VOID InlineHook::ResetASM() {

	DWORD oldAttributes = ModifyMemoryAttributes(s_originalAddress);

	memcpy(reinterpret_cast<void*>(s_originalAddress), s_originalBytes, CODE_LENGTH);

	ModifyMemoryAttributes(s_originalAddress, oldAttributes);

}
