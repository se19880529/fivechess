#include "stdafx.h"
#include <iostream>
using namespace std;
/*
#define INTMAX 0x7FFFFFFF
#define DISTANCE	5
#define DEFENCE 2
class QiPan{
public:
	QiPan(int);
	~QiPan();
	void Init();
	void SetChess(int x,int y, int c);
	void ClearChess(int x,int y);
	int GetChess(int x,int y);
	int GetNear(int x,int y);
	void Print();
	int GetSize() { return m_iSize;}
protected:
	int* m_iBuffer;
	short* m_iNear;
	int m_iSize;
};
QiPan::QiPan(int i):m_iSize(i) {
	m_iBuffer = new int[m_iSize*m_iSize];
	m_iNear = new short[m_iSize*m_iSize];
	memset(m_iBuffer, 0, m_iSize*m_iSize*sizeof(int));
	memset(m_iNear,0,m_iSize*m_iSize*sizeof(short));
};
void QiPan::Print() {
	cout<<endl<<"   ";
	for(int i=0;i<m_iSize;i++) {
		if(i<10)cout<<" ";
		cout<<i;
	}
	for(int i=0;i<m_iSize;i++) {
		cout<<endl;
		if(i<10)cout<<" ";
		cout<<i<<" ";
		for(int j=0;j<m_iSize;j++)
			if(m_iBuffer[i*m_iSize+j] <0) cout<<" X"; else if(m_iBuffer[i*m_iSize+j]>0) cout<<" O"; else cout<<" _";
	}
	cout<<endl;
}
QiPan::~QiPan() {delete[] m_iBuffer;}
void QiPan::ClearChess(int x, int y) {
	m_iBuffer[y*m_iSize+x] = 0;
	int temp;
	for(int i=1;i<DISTANCE;i++){
		if((temp=y*m_iSize+(x+i))>=0)m_iNear[temp]--;
		if((temp=y*m_iSize+(x-i))>=0)m_iNear[temp]--;
		if((temp=(y+i)*m_iSize+(x))>=0)m_iNear[temp]--;
		if((temp=(y-i)*m_iSize+(x))>=0)m_iNear[temp]--;
		if((temp=(y+i)*m_iSize+(x+i))>=0)m_iNear[temp]--;
		if((temp=(y-i)*m_iSize+(x+i))>=0)m_iNear[temp]--;
		if((temp=(y+i)*m_iSize+(x+i))>=0)m_iNear[temp]--;
		if((temp=(y-i)*m_iSize+(x+i))>=0)m_iNear[temp]--;
	}
}
void QiPan::SetChess(int x, int y, int c) {
	m_iBuffer[y*m_iSize+x] = c;
	int temp;
	for(int i=1;i<DISTANCE;i++){
		if((temp=y*m_iSize+(x+i))>=0)m_iNear[temp]++;
		if((temp=y*m_iSize+(x-i))>=0)m_iNear[temp]++;
		if((temp=(y+i)*m_iSize+(x))>=0)m_iNear[temp]++;
		if((temp=(y-i)*m_iSize+(x))>=0)m_iNear[temp]++;
		if((temp=(y+i)*m_iSize+(x+i))>=0)m_iNear[temp]++;
		if((temp=(y-i)*m_iSize+(x+i))>=0)m_iNear[temp]++;
		if((temp=(y+i)*m_iSize+(x+i))>=0)m_iNear[temp]++;
		if((temp=(y-i)*m_iSize+(x+i))>=0)m_iNear[temp]++;
	}
}
int QiPan::GetNear(int x,int y) {return m_iNear[y*m_iSize+x];}
int QiPan::GetChess(int x,int y) { return m_iBuffer[y*m_iSize+x];}
void QiPan::Init() {memcpy(m_iBuffer, 0, m_iSize*m_iSize*sizeof(int));}*/