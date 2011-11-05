// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
/*
#include "iostream"
#include "conio.h"
using namespace std;

class Human {
public:
	Human(char* name) {
		_name = new char[strlen(name)+1];
		strcpy(_name, name);
		cout<<"human init"<<endl;
	}
	~Human() {
		cout<<"human destory"<<endl;
		delete[] _name;
	}
	virtual void Tell() = 0;
protected:
	char* _name;
};
class Lady:public Human {
public:
	Lady(char* name):Human(name) {
	}
	void Tell() {
		FastTell(1,2,3);
		cout<<"*************This Miss "<<_name<<"**************"<<endl;
	}
	inline int FastTell(int a,int b,int c){
		//cout<<"Fast Miss "<<_name<<endl;
		return a+b;
	};
};
class Gentleman:public Human {
public:
	Gentleman(char* name):Human(name) {};
	void Tell() {
		cout<<"_____________This Mr "<<_name<<"________________"<<endl;
	}
};

class Father {
public:
	virtual void Show() {
		cout<<"Father"<<endl;
	}
};
class Son : public Father {
public:
	void Show(int a) {
		cout<<"Son"<<a<<endl;
	}
};
*/
// TODO: 在此处引用程序需要的其他头文件
