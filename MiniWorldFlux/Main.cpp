#include <Windows.h>
#include "Client.h"

#ifdef _DEBUG
LONG NTAPI NullptrHandler(struct _EXCEPTION_POINTERS* ExceptionInfo) {

	if (ExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_ACCESS_VIOLATION) {

		printf("-----------Start------------\n");
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
		printf("-----------End------------\n");
		MessageBoxA(nullptr, "Nullptr detected!", "Exception Handler:", MB_OK | MB_ICONERROR);
		return EXCEPTION_CONTINUE_EXECUTION;
	}

	return EXCEPTION_CONTINUE_SEARCH;
}
#endif

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved) {
	
	if (dwReason == DLL_PROCESS_ATTACH) {
#ifdef _DEBUG
		AddVectoredExceptionHandler(true, NullptrHandler);
#endif
		MakeDisposableThread(Client::startClient, hModule);
	}

	return TRUE;
}
