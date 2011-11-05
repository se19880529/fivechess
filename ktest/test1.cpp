#include "stdafx.h"
#include <iostream>
#define DWORD ""
#define DD DWORD
#undef DWORD
#define DWORD unsigned long
using namespace std;

class A {
public:
	virtual void VA() { cout<<"A::VA";}
};
class B {
public:
	int b;
	virtual void VB() { cout<<"B::VB";}
};
class C:public A,public B{
public:
	void VA() { cout<<"C::VA";}
	void VB() { cout<<"C::VB";}
protected:
	int b;
};
void test1main() {
	C c;
	A a;
	A* pa = static_cast<A*>(&c);
	B* pb = dynamic_cast<B*>(&a);
	cout<<"pa:"<<(DD)pa<<"pb:"<<(DD)pb;
}