#include "stdafx.h"
#include <iostream>
#include <vector>
#define STEPVALUE 10
using namespace std;


class Map {
public:
	Map(int size);
	~Map();
	int SetGoal(int _x,int _y);
	int SetBarrel(int _x,int _y);
	int GetPath(int x[],int y[], int size);
	int SetStart(int _x,int _y);
protected:
	int* m_iBuffer;
	int m_iSize;
	int m_iStartX;
	int m_iGoalX;
	int m_iGoalY;
	int m_iStartY;
private:
	void Init();
	vector<int> m_vPath;
	int* m_iParent;
	bool* m_bClosed;
	bool* m_bOpen;
	int* m_iHValue;
	int* m_iGValue;
};
void Map::Init() {
	for(int i=0;i<m_iSize*m_iSize;i++) {
		m_iParent[i] = -1;
		m_iGValue[i] = 0;
		m_iHValue[i] = 0;
		m_bOpen[i] = false;
		m_bClosed[i] = false;
	}
	m_bOpen[m_iStartX + m_iStartY*m_iSize] = true;
}
Map::Map(int size):m_iSize(size),m_iStartX(0),m_iStartY(0),m_iGoalX(0), m_iGoalY(0){
	m_iBuffer = new int[size*size];
	m_iParent = new int[size*size];
	m_bClosed = new bool[size*size];
	m_bOpen = new bool[size*size];
	m_iHValue = new int[size*size];
	m_iGValue = new int[size*size];
	for(int i=0;i<size*size;i++) {
		m_iBuffer[i] = 0;
		m_iParent[i] = -1;
		m_iHValue[i] = 0;
		m_iGValue[i] = 0;
		m_bClosed[i] = false;
		m_bOpen[i] = false;
	}
	m_iParent[0] = -1;
}
Map::~Map() {
	delete[] m_iBuffer;
	delete[] m_iParent;
	delete[] m_iHValue;
	delete[] m_iGValue;
	delete[] m_bClosed;
	delete[] m_bOpen;
}
int Map::SetGoal(int _x, int _y) {
	m_iGoalX = --_x;
	m_iGoalY = --_y;
	m_iBuffer[_x+_y*m_iSize] = 1;
	return 0;
}
int Map::SetBarrel(int _x, int _y) {
	m_iBuffer[(_x-1)+(_y-1)*m_iSize] = -1;
	return 0;
}
int Map::SetStart(int _x,int _y) {
	m_iParent[m_iStartX+m_iStartY*m_iSize] = -1;
	m_iStartX = _x-1;
	m_iStartY = _y-1;
	return 0;
}
int Map::GetPath(int x[], int y[], int size) {
	Init();
	bool end = false;
	int pX,pY,value,i,j;
	int X[4],Y[4];
	while(!end) {
		value = 0x7FFFFFFF;
		end = true;
		for(i=0;i<m_iSize*m_iSize;i++) {
			if(m_bOpen[i]) {
				end = false;
				if((m_iGValue[i]+m_iHValue[i])<value) {
					value = m_iGValue[i] + m_iHValue[i];
					pX = i%m_iSize;
					pY = i/m_iSize;
				}
				if(i%m_iSize == m_iGoalX && i/m_iSize == m_iGoalY) {
					pX = i%m_iSize;
					pY = i/m_iSize;
					end = true;break;
				}
				
			}
		}
		if(end)break;
		i = pX+pY*m_iSize;
		m_bOpen[i] = false;
		m_bClosed[i] = true;
		X[0] = X[1] = pX;X[2] = pX-1,X[3] = pX+1;
		Y[1] = pY+1,Y[0] = pY-1;Y[2]=Y[3]=pY;
		for(j=0;j<4;j++) {
			if(X[j]<m_iSize && X[j]>=0 && Y[j]<m_iSize && Y[j]>=0 && m_iBuffer[(X[j]=X[j]+Y[j]*m_iSize)]!=-1) {
				if(!m_bClosed[X[j]]) {
					if(m_bOpen[X[j]]) {
						if(m_iGValue[X[j]]>m_iGValue[i]+1*STEPVALUE) {
							m_iParent[X[j]] = i;
							m_iGValue[X[j]] = m_iGValue[i]+STEPVALUE;
						}
					}  else {
						m_iParent[X[j]] = i;
						m_iGValue[X[j]] = m_iGValue[i] + STEPVALUE;
						m_iHValue[X[j]] = (abs(m_iGoalY-(X[j]/m_iSize)) + abs(m_iGoalX-(X[j]%m_iSize)))*STEPVALUE;
						m_bOpen[X[j]] = true;
					}
				}
			}
		}
	}
	if(pX == m_iGoalX && pY == m_iGoalY) {
		int len = 0;
		int p = pX + pY*m_iSize;
		for(len=0;m_iParent[p]!=-1;len++,p = m_iParent[p]);
		if(size<len+1)return len+1;
		p = pX + pY*m_iSize;
		m_vPath.clear();
		for(int i=len;p!=-1;i--,p = m_iParent[p]) {
			x[i] = p%m_iSize+1;
			y[i] = p/m_iSize+1;
			m_vPath.insert(m_vPath.begin(),p);
		}
	/*绘制*/
	bool path = false;
	for(i=0;i<m_iSize;i++) { 
		for(j=0;j<m_iSize;j++) {
			path = false;
			int p = pX+pY*m_iSize;
			do{ 
				if(p==j*m_iSize+i)path = true;
			}while((p = m_iParent[p])!=-1);
			if(path)cout<<"0";
			else if(m_iBuffer[j*m_iSize+i] == -1)cout<<"X";
			else cout<<".";
		}
		cout<<endl;
	}
		return len+1;
	}
	return 0;
}
	
		

void mainastar() {
	int len,x,y;
	cin>>len;
	Map* m = new Map(len);
	char c = 0;
	while(c!='q') {
		cout<<endl<<"ASTAR?>";
		cin>>c;
		switch(c) {
			case 'b':
				cin>>x>>y;
				m->SetBarrel(x,y);
				break;
			case 's':
				cin>>x>>y;
				m->SetStart(x,y);
				cout<<endl<<"设置开始点位:"<<x<<","<<y;
				break;
			case 'g':
				cin>>x>>y;
				m->SetGoal(x,y);
				cout<<endl<<"设置目标点位:"<<x<<","<<y;
				break;
		}
	}
	int xx[400],yx[400];
	int l = m->GetPath(xx,yx,400);
	cout<<endl<<"计算完成，共需"<<l<<"步："<<endl;
	cout<<"("<<xx[0]<<","<<yx[0]<<")";
	for(int i=1;i<l;i++) {
		cout<<"-->("<<xx[i]<<","<<yx[i]<<")";
	}
}