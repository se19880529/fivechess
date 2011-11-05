#include "stdafx.h"
#include <iostream>
#include <vector>
using namespace std;

vector<int> vt;

void vectortest() {
	vt.push_back(1);
	vt.push_back(2);
	vt.push_back(3);
	vector<int>::iterator iter = vt.begin();
	for(;iter!=vt.end();iter++) {
		cout<<*iter;
		//vt.swap
		vt.erase(iter);
	}
}