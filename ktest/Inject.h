#pragma once
#include <iostream>
#include <string.h>
#include <windows.h>
using namespace std;
class CInject
{
public:
	CInject(void);
	~CInject(void);
	inline BOOL Ready() { return bReady; }
	int DoInject(wstring filename, DWORD ProcessID);
protected:
	BOOL bReady;
};
