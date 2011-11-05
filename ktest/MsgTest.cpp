#include "stdafx.h"
#include <windows.h>
#include <queue>
#include <iostream>
using namespace std;

class CMessagePipe {
public:
	CMessagePipe();
	int PostAMessage(UINT msg, WPARAM wParam, LPARAM lParam);
	int PeekAMessage(MSG *msg, int remove);
protected:
	int InsertMessage(UINT msg, WPARAM wparam, LPARAM lparam);
	int GetAMessage(MSG *msg);
	CRITICAL_SECTION cs;
	queue<UINT> message;
	queue<WPARAM> wparam;
	queue<LPARAM> lparam;
};

CMessagePipe::CMessagePipe() {
	InitializeCriticalSection(&cs);
}
int CMessagePipe::GetAMessage(MSG *msg) {
	if(!message.empty()) {
		EnterCriticalSection(&cs);
		msg->message = message.front();
		message.pop();
		msg->wParam = wparam.front();
		wparam.pop();
		msg->lParam = lparam.front();
		lparam.pop();
		LeaveCriticalSection(&cs);
		return 1;
	}
	return 0;
}
int CMessagePipe::InsertMessage(UINT msg, WPARAM wp, LPARAM lp) {
	EnterCriticalSection(&cs);
	message.push(msg);
	wparam.push(wp);
	lparam.push(lp);
	LeaveCriticalSection(&cs);
	return 1;
}
int CMessagePipe::PeekAMessage(MSG *msg, int remove) {
	if(msg==NULL)return 0;
	return GetAMessage(msg);
}
int CMessagePipe::PostAMessage(UINT msg, WPARAM wParam, LPARAM lParam) {
	return InsertMessage(msg,wParam,lParam);
}
#define WM_TEST WM_USER+80
#define WM_STOP WM_USER+90
HANDLE hEvent;
#define USEPIPE
//#define USEEVENT
int time[1000];   //记录延时时间
int time2[1000];
CMessagePipe cp;
DWORD WINAPI PeekMessageThread(LPVOID param)
{
	int k=0;
	MSG msg;
	while(1)
	{
		int i;
#ifdef USEEVENT
		WaitForSingleObject(hEvent,INFINITE);
#endif
#ifdef USEPIPE
		i=cp.PeekAMessage(&msg,1);
#else
		i=PeekMessage(&msg,NULL,0,0,PM_REMOVE);
#endif
	if(0!=i)
	{
		if(msg.message==WM_TEST)
		{
			LARGE_INTEGER nCounter1,nCounter2,nCounter3,nFrequency;
			QueryPerformanceCounter(&nCounter2);
			QueryPerformanceFrequency(&nFrequency);//QueryPerformanceCounter(&nFrequency);
			//cout<<"接收到WM_TEST"<<endl;
			int a,t;
			nCounter1=*(LARGE_INTEGER*)msg.lParam;
			a=*((int*)(msg.wParam));
			t=(1000*1000*(nCounter2.QuadPart-nCounter1.QuadPart))/(double)nFrequency.QuadPart;
			time[k]=t;
			QueryPerformanceCounter(&nCounter3);
			t=(1000*1000*(nCounter3.QuadPart-nCounter2.QuadPart))/(double)nFrequency.QuadPart;
			time2[k]=t;
			k++;
			//cout<<"接收到的数据是："<<a<<"   WindowsMessage传递耗费了"<<t<<"微妙"<<endl;
		}else if(msg.message==WM_STOP)
		{
			LARGE_INTEGER nCounter1,nCounter2,nFrequency;
			QueryPerformanceCounter(&nCounter2);
			QueryPerformanceFrequency(&nFrequency);
			nCounter1=*(LARGE_INTEGER*)msg.lParam;
			int t=1000*1000*(nCounter2.QuadPart-nCounter1.QuadPart)/(double)nFrequency.QuadPart;
			cout<<"接收WM_STOP消息，花费了"<<t<<"微妙"<<endl;
			cout<<"Test Stop!"<<endl;
			break;
		}
	}
	}
	return 0;
}

int mainmsg()
{
	
	hEvent = CreateEvent(NULL,FALSE,FALSE, "event");
	HANDLE hThread;
	DWORD threadID;
	hThread=CreateThread(NULL,0,PeekMessageThread,NULL,0,&threadID);
	Sleep(5000);
	WPARAM wParam;
	LPARAM lParam;
	int j=6;
	wParam=(WPARAM)&j;
	LARGE_INTEGER nCounter1[1000];
	for(int i=0;i<1000;i++)
	{
	QueryPerformanceCounter(&nCounter1[i]);
    lParam=(LPARAM)&nCounter1[i];
#ifdef USEPIPE
	cp.PostAMessage(WM_TEST,wParam,lParam);
#else
	PostThreadMessage(threadID,WM_TEST,wParam,lParam);
#endif
#ifdef USEEVENT
	SetEvent(hEvent);
	Sleep(30);
#endif

	Sleep(10);
	}
	Sleep(5000);
	QueryPerformanceCounter(&nCounter1[0]);
	lParam=(LPARAM)&nCounter1;
#ifdef USEPIPE
	cp.PostAMessage(WM_STOP,wParam,lParam);
#else	
	PostThreadMessage(threadID,WM_STOP,wParam,lParam);
#endif
	cout<<"发送WM_TEST耗时："<<endl;
	for(int i=0;i<1000;i++)
	{
		cout<<time[i]<<"  ";
	}
	cout<<endl;
	cout<<"每个Peek循环耗时："<<endl;
    for(int i=0;i<10;i++)
	{
		cout<<time2[i]<<"  ";
	}
	cout<<endl;

	cin.get();

	return 0;
}