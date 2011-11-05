// ktest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Inject.h"
#include <stdarg.h>
#include <iostream>
#include <conio.h>
#include <queue>
#define DWORD unsigned long
#pragma pack(push)
#pragma pack(8)
using namespace std;
struct foo {
	char a;
	char b;
	double c;
};
#pragma pack(pop)
struct ffoo {
	char b;
	short a;
	foo f;
};


class cfoo {
protected:
	static const  int v = 1;
	int value[v];
public:
	cfoo() {
		value[0] = 0;
	}
	void inc() {
		value[0]++;
	}
};
class empty {
};


union test
{
	char a[2];
	int  b;
};

int Partition(int a[], int lo, int hi) {
	int i = lo-1;
	int x = a[hi],temp;
	for(int j=lo;j<hi-1;j++) {
		if(a[j]<x) {
			i++;
			temp = a[j];
			a[j] = a[i];
			a[i] = temp;
		}
	}
	temp = a[i+1];
	a[i+1] = a[hi];
	a[hi] = temp;
	return i+1;
}

void QuikSort(int a[], int lo, int hi) {
	int f;
	if(lo<hi) {
		f = Partition(a,lo, hi);
		QuikSort(a, f+1, hi);
		QuikSort(a, lo, f-1);
	}
}

void SiftDown(int H[], int n, int i) {
	bool end = false;
	int p = i,temp;
	if(2*i<=n) {
		while((p=p*2)<=n && !end) {
			if((p+1)<=n && H[p+1]<H[p]) p++;
			if(H[p/2]>H[p]) {
				temp = H[p];
				H[p] = H[p/2];
				H[p/2] = temp;
			} else end = true;
		}
	}
}

void HeapSort(int H[], int n) {
	H[n] = H[0];
	for(int i=n/2;i>=1;i--) {
		SiftDown(H, n, i);
	}
	int temp;
	for(int i=n;i>=1;i--) {
		temp = H[i];
		H[i] = H[1];
		H[1] = temp;
		SiftDown(H, i, 1);
	}
}

void BubleSort(int a[], int size) {
	int temp;
	for(int i=size-1;i>0;i--) 
		for(int j=0;j<i-1;j++) {
			if(a[j]>a[j+1]) {
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
		}
}
/*
int Lady::FastTell(){
	cout<<"Fast Miss "<<_name<<endl;
	return 0;
}
*/
	
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
int  encode(const  void*  raw_in,  void*  raw_out,  uint32_t  password,  size_t  len) 
{ 
	const  uint8_t*  in  =  (const  uint8_t*)raw_in; 
	uint8_t*  out  =  (uint8_t*)raw_out; 

	uint32_t  seed  =  password  ^  0xc8b58d63u; 
	for  (size_t  i  =  0  ;  i  <  len;  ++i)  { 
		uint8_t  a  =  (  in[i]  ^  seed  )  >>  4; 
		uint8_t  b  =  (  (  ((uint32_t)in[i])  <<  18  )  ^  seed  )  >>  (18-4); 
		a  &=  15; 
		b  &=  240; 
		a  =  15  &  (  a  ^  (b  <<  3)); 
		out[i]  =  a  |  b; 
		seed  =  (seed  *  608347  ^  seed  ^  in[i]); 
	} 
	return 1;
} 


int  decode(const  void*  raw_in,  void*  raw_out,  uint32_t  password,  size_t  len) 
{ 
const  uint8_t*  in  =  (const  uint8_t*)raw_in; 
uint8_t*  out  =  (uint8_t*)raw_out; 
uint8_t a,b;
uint32_t  seed  =  password  ^  0xc8b58d63u; 
	for  (size_t  i  =  0  ;  i  <  len;  ++i)  { 
	//  请在此处补全代码 
		a = (in[i]&15);
		b = (in[i]&240);
		a = ((a<<4)^seed)&240;
		b = (((b<<(18-4))^seed)>>18)&15;
		out[i] = a|b;
		seed = (seed*608347^seed^out[i]);
	} 
	return 1;
} 
class CFenShu {
public:
	CFenShu();
	CFenShu(int Fenzi, int Fenmu);
	CFenShu(CFenShu& f);
	void YueFen();
	int m_fenmu;
	int m_fenzi;
};
class DaShu {
protected:
	string _buf;
public:
	DaShu():_buf("0"){};
	DaShu(int i);
	DaShu(DaShu&);
	DaShu(string s);

	string invert() const;
	string get() const;
	DaShu operator+(const DaShu& d) const;
	DaShu operator-(const DaShu& d) const;
	DaShu operator*(const DaShu& d) const;
	DaShu Div(const DaShu& d,DaShu& rem) const;
	DaShu& operator=(const DaShu& d);
	bool operator==(const DaShu& d) const;
	bool operator<(const DaShu& d) const;
	bool operator>(const DaShu& d) const;
};
void GetLCM(int fenzi[], int fenmu[], int size, DaShu& lcmfenzi, DaShu& lcmfenmu);
int __main();
int  t_main() 
{ 
	__main();

/*
CFenShu f;
cout<<"分母：";cin>>f.m_fenmu;
cout<<endl<<"分子：";cin>>f.m_fenzi;
cout<<endl;
f.YueFen();
cout<<"约分后："<<f.m_fenzi<<" "<<f.m_fenmu<<endl;
*/

return 1;
} 












void func(int a,int b,int c) {
	cout<<a<<" "<<b<<" "<<c;
	
}


queue<int> q;
int main2800();
int mainmsg();
int main3101r2();
void mainheap();
void mainastar();
void maindijsktra();
void mainhuffman();
void mainquicksort();
void fiveplay();
void kmpmain();
void arrsummain();
void ptrtestmain();int mainsougou();
void mallocmain();
void vectortest();
void baidu1027test();
	int x = 5;
	void test1main();
int _tmain(int argc, _TCHAR* argv[])
{
	//t_main();
	//mainsougou();
	//mallocmain();
//fiveplay();
	test1main();
	/*
	DWORD id;
	cout<<"输入进程号"<<endl;
	cin>>id;
	CInject ci;
	HANDLE h = ::CreateEventW(NULL, FALSE, TRUE, L"MyVirusEvent");
	ci.DoInject(L"C:\\Users\\Eagle\\Documents\\Visual Studio 2008\\Projects\\virus\\Debug\\virus.dll", id);
	Sleep(1000);
	SetEvent(h);*/
	//cout<<GetSystemTimeAdjustment
	/*
	int i=1;
	while(i!=0) {
		cin>>i;
		q.push(i);
	}
	cout<<endl;
	while(!q.empty()) {
		cout<<q.front()<<" ";
		q.pop();
	}
	*/
	getch();
	return 0;
}

