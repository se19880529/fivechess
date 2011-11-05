#include "stdafx.h"
#include <iostream>
using namespace std;
#define DWORD unsigned long
struct pack {
	int n:3;
	unsigned short s:3;
};
char str1[18];
int n1;
int n2;
char str2[25];
void ptrtestmain() {
	cout<<(DWORD)str1<<" "<<(DWORD)&n1<<" "<<(DWORD)&n2<<" "<<(DWORD)str2<<" "<<(DWORD)(str1-str2);
}