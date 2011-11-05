#include "stdafx.h"
#include "ThreadPool.h"
using namespace threadpool;
CThreadPool::CThreadPool(int n, bool sys):m_iLength(n) {
	m_bSystem = sys;
	if(!sys) {
		InitializeCriticalSection(&cs);
		m_hExit = CreateEvent(NULL,FALSE,FALSE,NULL);
		m_iWorkNumber = 0;
		m_hWork = CreateSemaphore(NULL,0,0x7FFFFFFF,NULL);
		tagThreadParam* p = new tagThreadParam, &tp = *p;
		tp.hExit = m_hExit;
		tp.hWork = m_hWork;
		tp.piWorkNumber = &m_iWorkNumber;
		tp.pwHead = &m_wHead;
		tp.pcs = &cs;
		m_wHead.next = &m_wHead;
		m_wHead.pre = &m_wHead;
		m_hThread = new HANDLE[n];
		DWORD id;
		for(int i=0;i<m_iLength;i++)m_hThread[i] =CreateThread(NULL,0, CThreadPool::WorkThread, (LPVOID)&tp,0,&id);
	}
}
CThreadPool::~CThreadPool() {
	if(!m_bSystem) {
		SetEvent(m_hExit);
		WaitForMultipleObjects(m_iLength, m_hThread, TRUE, INFINITE);
		delete[] m_hThread;
	}
}
int CThreadPool::AddWork(WorkProc proc, PVOID param) {
	if(!m_bSystem) {
		WorkInfo* wi = new WorkInfo;
		wi->pvParam = param;
		wi->wpProc = proc;
		wi->next = &m_wHead;
		EnterCriticalSection(&cs);
		wi->pre = m_wHead.pre;
		m_wHead.pre->next = wi;
		m_wHead.pre = wi;
		LeaveCriticalSection(&cs);
		ReleaseSemaphore(m_hWork, 1, NULL);
		::InterlockedIncrement((volatile LONG *)&m_iWorkNumber);
	} else {
	}
	return 0;
}
DWORD CThreadPool::WorkThread(PVOID p) {
	tagThreadParam* tp = (tagThreadParam*)p;
	HANDLE ev[2];
	ev[0] = tp->hExit;
	ev[1] = tp->hWork;
	WorkInfo* wi;
	while(1) {
		DWORD res = WaitForMultipleObjects(2, ev, FALSE,INFINITE);
		if(res == WAIT_OBJECT_0) {
			break;
		} else if(res == WAIT_OBJECT_0+1) {
			EnterCriticalSection(tp->pcs);
			wi = tp->pwHead->next;
			if(wi!=tp->pwHead) {
				wi->next->pre = tp->pwHead;
				tp->pwHead->next = wi->next;
			}
			LeaveCriticalSection(tp->pcs);
			if(wi!=tp->pwHead) {
				if(wi->wpProc) {
					(wi->wpProc)(wi->pvParam);
				}
				delete wi;
				::InterlockedDecrement((volatile LONG *)tp->piWorkNumber);
			}
		}
	}
	return 0;
}