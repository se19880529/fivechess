#include "stdafx.h"
#include <iostream>
using namespace std;

class Pattern {
public:
	Pattern(char* c);
	~Pattern();
	void Init(char* c);
	int Find(char* c);
protected:
	int GetNexts();
	char* pattern;
	int len;
	int* nexts;
};
Pattern::Pattern(char *c):pattern(NULL),nexts(NULL) {
	Init(c);
}
Pattern::~Pattern() {
	delete[] pattern;
	delete[] nexts;
}
void Pattern::Init(char *c) {
	if(pattern!=NULL)delete[] pattern;
	if(nexts!=NULL)delete[] nexts;
	pattern = new char[strlen(c)+1];
	nexts = new int[strlen(c)];
	len = strlen(c);
	memcpy(pattern,c,strlen(c)+1);
	GetNexts();
}
int Pattern::GetNexts() {
	int i=-1,j=0;
	nexts[0] = -1;
	while(j<len-1) {
		if(i==-1 || pattern[i] == pattern[j]) {
			i++,j++;
			nexts[j] = i;
			while(nexts[j]==pattern[j])nexts[j] = nexts[nexts[j]];
		} else i = nexts[i];
	}
	return 0;
}
int Pattern::Find(char *c) {
	int l = strlen(c);
	int i,k;
	for(i=0,k=0;i<l;i++) {
		if(pattern[k]!=c[i]) {
			k = nexts[k];
			i--;
			if(k == -1)k= 0,i++;
		} else k++;
		if(k == len)break;
	}
	return i-k+1;
}
void kmpmain() {
	char pt[50];
	char str[500];
	cin>>pt;
	Pattern* p = new Pattern(pt);
	while(1) {
		cin>>str;
		cout<<endl<<(&str[p->Find(str)])<<endl;
	}
}