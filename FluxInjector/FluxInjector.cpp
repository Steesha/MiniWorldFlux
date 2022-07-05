#include <iostream>
#include <Windows.h>

#include <tlhelp32.h>
using namespace std;
int main()
{
	cout << "[Flux] for miniwordld" << endl;
	//获取当前目录
	TCHAR Buffer[MAX_PATH];
	DWORD dwRet;
	dwRet = GetModuleFileName(NULL, Buffer, MAX_PATH);

	if (dwRet == 0 || dwRet > MAX_PATH)
	{
		cout << "[Flux] Fatel Error(0x000)" << endl;
		system("pause");
		return -1;
	}
	wstring dir = Buffer;
	wstring sReturn = L"";
	sReturn.append(dir);
	int nFindLast = sReturn.find_last_of(L"\\");
	sReturn = sReturn.substr(0, nFindLast + 1);

	dir = sReturn;
	wcout << L"[Flux] CurrentDirectory:" << dir.c_str() << endl;

	wstring file = dir + L"\\MiniWorldFlux.dll";

	//检查DLL是否存在
	HANDLE fHandle = CreateFileW(file.c_str(), GENERIC_ALL, 0, 0, OPEN_EXISTING, 0, 0);
	if (fHandle == INVALID_HANDLE_VALUE)
	{
		cout << "[Flux] 请将MiniWorldFlux.dll与本注入器放在同一文件夹下或检查dll是否被占用" << endl;
		system("pause");
		return -1;
	}

	CloseHandle(fHandle);

	//文件存在，打开迷你世界进程
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	HANDLE hProcess = INVALID_HANDLE_VALUE;
	if (Process32First(snapshot, &entry) == TRUE)
	{
		while (Process32Next(snapshot, &entry) == TRUE)
		{
			if (_wcsicmp(entry.szExeFile, L"iworldpc3.exe") == 0)
			{
				hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);
				break;
			}
		}
	}
	CloseHandle(snapshot);

	if (hProcess == INVALID_HANDLE_VALUE)
	{
		cout << "[Flux] 请运行游戏后再进行注入" << endl;
		system("pause");
		return -1;
	}

	int size = file.size() * 2 + 1;
	//可以进行注入
	PVOID addr = VirtualAllocEx(hProcess, NULL, size, MEM_COMMIT, PAGE_READWRITE);
	if (addr == NULL)
	{
		cout << "[Flux] 内存空间申请失败，请稍后再试" << endl;
		CloseHandle(hProcess);
		system("pause");
		return -1;
	}

	int retval = WriteProcessMemory(hProcess, addr, (LPVOID)file.c_str(), size, NULL);
	if (retval == 0)
	{
		cout << "[Flux] 内存写入失败，请稍后再试" << endl;
		CloseHandle(hProcess);
		system("pause");
		return -1;
	}

	HMODULE module = GetModuleHandle(L"kernel32.DLL");
	if (module == NULL)
	{
		cout << "[Flux] 获取远程地址失败" << endl;
		CloseHandle(hProcess);
		system("pause");
		return -1;
	}
	PTHREAD_START_ROUTINE pfnThread = (PTHREAD_START_ROUTINE)GetProcAddress(module, "LoadLibraryW");
	if (pfnThread == NULL)
	{
		cout << "[Flux] 获取远程地址失败" << endl;
		CloseHandle(hProcess);
		system("pause");
		return -1;
	}


	HANDLE hRemoteThread = CreateRemoteThread(
		hProcess,//in   HANDLE hProcess,  
		NULL,
		0,//__in   SIZE_T dwStackSize,  
		pfnThread,
		addr,
		0,
		NULL);

	if (hRemoteThread == INVALID_HANDLE_VALUE)
	{
		cout << "[Flux] 注入失败" << endl;
		CloseHandle(hProcess);
		system("pause");
		return -1;
	}

	CloseHandle(hProcess);
	cout << "[Flux] FluxClient注入成功！" << endl;
	system("pause");
	return 0;
}