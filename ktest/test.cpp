#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <vector>
using namespace std;
#define TIME	1

LARGE_INTEGER f,t;
void MallocVer(vector<int>& v) {
	int* i;
	//for(unsigned long j = 0;j<TIME;j++) {
		i = (int*)malloc(50);
		/*
		*i = 1;
		v.push_back(*i);
		free(i);
	}*/
}
void StackVer(vector<int>& v) {
	int i;
	//for(unsigned long j =0;j<TIME;j++) {
		i = 1;
	//	v.push_back(i);
	//}
}

void StartClock() {
	::QueryPerformanceFrequency(&f);
	::QueryPerformanceCounter(&t);
}

__int64 Stop() {
	LARGE_INTEGER li;
	::QueryPerformanceCounter(&li);
	return (li.QuadPart-t.QuadPart)*1000000/f.QuadPart;
}

void Test() {
	vector<int> v;
	int i,*p;
	__int64 m,s;
	StartClock();
	//MallocVer(v);
		p = (int*)malloc(50);
		//free(p);
	m = Stop();
	StartClock();
	//StackVer(v);
	i = 0;
	s = Stop();
	cout<<"用malloc运行时间："<<m<<"微秒"<<endl<<"不用malloc运行时间："<<s<<"微秒"<<endl;
}