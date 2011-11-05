#include "stdafx.h"
#include <windows.h>
namespace threadpool {
	typedef DWORD (*WorkProc)(PVOID);
	struct WorkInfo {
		WorkProc wpProc;
		PVOID pvParam;
		WorkInfo* next;
		WorkInfo* pre;
	};
	class CThreadPool {
	public:
		CThreadPool(int n, bool system = false);
		~CThreadPool();
		int AddWork(WorkProc proc, PVOID param);
	protected:
		struct tagThreadParam {
			WorkInfo* pwHead;
			HANDLE hExit;
			HANDLE hWork;
			CRITICAL_SECTION* pcs;
			int* piWorkNumber;
		};
		static DWORD WINAPI WorkThread(PVOID);
		HANDLE* m_hThread;
		int m_iLength;
		HANDLE m_hExit;
		HANDLE m_hWork;
		bool m_bSystem;
		int m_iWorkNumber;
		WorkInfo m_wHead;
		CRITICAL_SECTION cs;
	};
}
	