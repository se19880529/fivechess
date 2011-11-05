#include "StdAfx.h"
#include "Inject.h"

CInject::CInject(void):bReady(FALSE)
{
	HANDLE hToken = NULL;
	if(OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken)) {
		TOKEN_PRIVILEGES tp;
		LUID luid;
		LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luid);
		tp.PrivilegeCount = 1;
		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		tp.Privileges[0].Luid = luid;
		if(AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL))bReady = TRUE;
		CloseHandle(hToken);
	}
}

CInject::~CInject(void)
{
	HANDLE hToken = NULL;
	if(OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken)) {
		TOKEN_PRIVILEGES tp;
		LUID luid;
		LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luid);
		tp.PrivilegeCount = 1;
		tp.Privileges[0].Attributes = 0;
		tp.Privileges[0].Luid = luid;
		if(AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL))bReady = FALSE;
	}
}

int CInject::DoInject(std::wstring filename, DWORD ProcessID) {
	HANDLE hPro;
	char* buffer;
	hPro = OpenProcess(PROCESS_QUERY_INFORMATION|
		PROCESS_CREATE_THREAD     |
		PROCESS_VM_OPERATION		|
		PROCESS_VM_WRITE
		
		, FALSE, ProcessID);
	if(NULL == hPro) return 1;
	int i = filename.length();
	buffer = (char*)VirtualAllocEx(hPro,NULL, (filename.length()+1)*sizeof(wchar_t), MEM_COMMIT, PAGE_READWRITE);
	BOOL b = WriteProcessMemory(hPro, buffer, filename.c_str(), (filename.length()+1)*sizeof(wchar_t), NULL);
	DWORD tid;
	HMODULE h = GetModuleHandle("Kernel32");
	LPVOID fun = GetProcAddress(h, "LoadLibraryW");
	HANDLE thread = CreateRemoteThread(hPro, NULL,0, (LPTHREAD_START_ROUTINE)fun, (LPVOID)buffer, 0, &tid);
	if(thread == NULL) return 2;
	CloseHandle(hPro);
	CloseHandle(thread);
	return 0;
}
	
	