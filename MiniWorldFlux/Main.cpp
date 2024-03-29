#include "pch.h"
#include "Client.h"

#define _FLUX_DEBUG_SKIP_WINAPI
#ifdef _DEBUG
LONG NTAPI NullptrHandler(struct _EXCEPTION_POINTERS* ExceptionInfo) {

#ifndef _FLUX_DEBUG_SKIP_WINAPI
	DWORD errAddr = reinterpret_cast<DWORD>(ExceptionInfo->ExceptionRecord->ExceptionAddress);
	if (ExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_ACCESS_VIOLATION) {
#else
	constexpr unsigned int fn1Length = 0xAF;
	DWORD pFn1 = reinterpret_cast<DWORD>(IsBadReadPtr);
	DWORD errAddr = reinterpret_cast<DWORD>(ExceptionInfo->ExceptionRecord->ExceptionAddress);
	if (ExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_ACCESS_VIOLATION
		&& errAddr < pFn1
		&& errAddr >(pFn1 + fn1Length)) {
#endif

		printf("-----------Nullptr------------\n");
		printf("Nullptr in: %p\n", ExceptionInfo->ExceptionRecord->ExceptionAddress);
		printf("EAX: %X\n", ExceptionInfo->ContextRecord->Eax);
		printf("EBX: %X\n", ExceptionInfo->ContextRecord->Ebx);
		printf("ECX: %X\n", ExceptionInfo->ContextRecord->Ecx);
		printf("EDX: %X\n", ExceptionInfo->ContextRecord->Edx);
		printf("EDI: %X\n", ExceptionInfo->ContextRecord->Edi);
		printf("ESI: %X\n", ExceptionInfo->ContextRecord->Esi);
		printf("ESP: %X\n", ExceptionInfo->ContextRecord->Esp);
		printf("EBP: %X\n", ExceptionInfo->ContextRecord->Ebp);
		printf("EIP: %X\n", ExceptionInfo->ContextRecord->Eip);

		printf("-----------Stack------------\n");
		DWORD esp = ExceptionInfo->ContextRecord->Esp;
		DWORD ebp = ExceptionInfo->ContextRecord->Ebp;
		int inc = 100;
		while (inc-- > 0) {
			printf("[EBP+%X] %X\n", inc * 4, *(DWORD*)(ebp));
			ebp += 4;
		}
		printf("-----------End------------\n");

		MessageBoxA(nullptr, "Nullptr detected!", "Exception Handler:", MB_OK | MB_ICONERROR);

		return EXCEPTION_CONTINUE_EXECUTION;
	}

	return EXCEPTION_CONTINUE_SEARCH;
}
#endif

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved) {
	VM_LION_WHITE_START
	
	if (dwReason == DLL_PROCESS_ATTACH) {
#ifdef _DEBUG
		AddVectoredExceptionHandler(true, NullptrHandler);
#endif
		MakeDisposableThread(Client::startClient, hModule);
	}

	return TRUE;
	VM_LION_WHITE_END
}
