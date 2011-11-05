#include "stdafx.h"
#include "timer.h"
LARGE_INTEGER f,t;
__int64 Start() {
	QueryPerformanceFrequency(&f);
	QueryPerformanceCounter(&t);
	return t.QuadPart;
}
__int64 Stop() {
	LARGE_INTEGER t2;
	QueryPerformanceCounter(&t2);
	return (t2.QuadPart-t.QuadPart)*1000*1000/f.QuadPart;
}
__int64 GetTime() {
	LARGE_INTEGER t2;
	QueryPerformanceCounter(&t2);
	return t2.QuadPart;
}
void StopCout(char* c) {
	__int64 t = Stop();
	cout<<endl<<c<<"ºÄÊ±"<<t<<"Î¢Ãë"<<endl;
}