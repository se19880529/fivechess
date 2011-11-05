// WindowsMessageTimeDelayTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<Windows.h>
#include<conio.h>
#include<iostream>
using namespace std;
#define WM_TEST WM_USER+80
#define WM_STOP WM_USER+90

int time[20];   //记录延时时间
int time2[20];

DWORD WINAPI PeekMessageThread(LPVOID param)
{
	int k=0;
	MSG msg;
	while(1)
	{
		int i=PeekMessage(&msg,NULL,0,0,PM_REMOVE);
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

int _tmain(int argc, _TCHAR* argv[])
{
	
	
	HANDLE hThread;
	DWORD threadID;
	hThread=CreateThread(NULL,0,PeekMessageThread,NULL,0,&threadID);
	Sleep(5000);
	WPARAM wParam;
	LPARAM lParam;
	int j=6;
	wParam=(WPARAM)&j;
	LARGE_INTEGER nCounter1;
	QueryPerformanceCounter(&nCounter1);
    lParam=(LPARAM)&nCounter1;
	for(int i=0;i<10;i++)
	{
	PostThreadMessage(threadID,WM_TEST,wParam,lParam);
	Sleep(10);
	}
	//Sleep(5000);
	QueryPerformanceCounter(&nCounter1);
	lParam=(LPARAM)&nCounter1;
	PostThreadMessage(threadID,WM_STOP,wParam,lParam);
	cout<<"发送WM_TEST耗时："<<endl;
	for(int i=0;i<10;i++)
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

	getch();

	return 0;
}

