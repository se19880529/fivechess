#include "stdafx.h"
#include <iostream>
using namespace std;
#define INTMAX 0x7FFFFFFF

class Graph {
public:
	Graph(int);
	~Graph();
	int GetShort(int* path,int size, int a,int b);
	int GetShortFloyd(int* path,int size, int a,int b);
	void AddArc(int a,int b,int w);
	void PrintArc();
protected:
	int Dijkstra(int* path, int size, int a,int b);
	void Floyd(int len[], int parent[]);
	int* m_iPath;
	int* m_iLength;
	bool again;
private:
	int* m_iMatrix;
	int m_iSize;
};
int Graph::GetShortFloyd(int* path,int size, int a,int b) {
	if(again) {
		if(m_iPath == NULL) {
			m_iPath = new int[m_iSize*m_iSize];
			m_iLength = new int[m_iSize*m_iSize];
		}
		Floyd(m_iLength,m_iPath);
		again = false;
	}
	int len,i;
	int p = a;
	for(len=0;p!=b;len++,p=m_iPath[p*m_iSize+b]);
	if(size<len+1)return len+1;
	p = a;
	for(i=0;p!=b;i++,p=m_iPath[p*m_iSize+b])path[i] = p;
	path[i] = b;
	return len+1;
}

void Graph::Floyd(int len[], int path[]) {
	for(int i=0;i<m_iSize;i++)
		for(int j=0;j<m_iSize;j++) {
			len[i*m_iSize+j] = m_iMatrix[i*m_iSize+j];
			path[i*m_iSize+j] = j;
		}
	for(int i=0;i<m_iSize;i++)
		for(int j=0;j<m_iSize;j++)
			for(int k=0;k<m_iSize;k++)
				if(len[j*m_iSize+i]!=INTMAX && len[i*m_iSize+k]!=INTMAX)
					if(len[j*m_iSize+i] + len[i*m_iSize+k]<len[j*m_iSize+k]) {
						len[j*m_iSize+k] = len[j*m_iSize+i] + len[i*m_iSize+k];
						path[j*m_iSize+k] = path[j*m_iSize+i];
					}
}
		
Graph::Graph(int s):m_iSize(s),m_iPath(NULL),m_iLength(NULL),again(true) {
	m_iMatrix = new int[s*s];
	for(int i=0;i<s*s;i++) {	
		m_iMatrix[i] = INTMAX;
		if(i%s == i/s)m_iMatrix[i] = 0;
	}
}
Graph::~Graph() { delete[] m_iMatrix;}
void Graph::AddArc(int a, int b, int w) {
	m_iMatrix[a*m_iSize+b] = w;
	again = true;
}
void Graph::PrintArc() {
	int len = 0;
	for(int i=0;i<m_iSize*m_iSize;i++) {
		if(m_iMatrix[i]!=INTMAX && i%m_iSize!=i/m_iSize) {
			cout<<endl<<"ARC"<<++len<<":"<<i/m_iSize<<"---"<<m_iMatrix[i]<<"-->"<<i%m_iSize;
		}
	}
	cout<<endl<<"共有"<<len<<"条弧";
}
void swap(int& a,int& b) {
	int t = a;
	a = b;
	b = t;
}
int Graph::Dijkstra(int path[], int size, int a, int b) {
	int lens = 1;
	int* buff = new int[m_iSize],*weight = new int[m_iSize], *parent = new int[m_iSize];
	for(int i=0;i<m_iSize;i++){buff[i] = i;weight[i] = m_iMatrix[a*m_iSize + i];parent[i] = a;};
	swap(buff[0],buff[a]);
	bool goon = true;
	int min,minind;
	while(goon) {
		min = INTMAX;
		minind = -1;
		for(int i = lens;i<m_iSize;i++) {
			if(weight[buff[i]]<min) {
				min = weight[buff[i]];
				minind = i;
			}
		}
		if(minind == -1)break;
		for(int i = lens;i<m_iSize;i++) {
			if(m_iMatrix[buff[minind]*m_iSize + buff[i]] != INTMAX && 
				m_iMatrix[buff[minind]*m_iSize + buff[i]]+weight[buff[minind]] < weight[buff[i]]) {
					parent[buff[i]] = buff[minind];
					weight[buff[i]] = m_iMatrix[buff[minind]*m_iSize + buff[i]]+weight[buff[minind]];
			}
		}
		if(buff[minind] == b)goon = false;
		swap(buff[minind], lens);
		lens++;
	}
	if(goon)return -1;
	else {
		int len = 0;
		int p = b;
		for(;p!=a;p = parent[p],len++);
		if(size<len+1)return len+1;
		p = b;
		for(int i=len;p!=a;p=parent[p],i--)path[i] = p;
		path[0] = a;
		return len+1;
	}
	delete[] weight;
	delete[] buff;
	delete[] parent;
}
int Graph::GetShort(int* p, int size, int a,int b) {
	return Dijkstra(p, size,a,b);
}
void maindijsktra() {
	int size;
	cin>>size;
	Graph* g = new Graph(size);
	char c = 0;
	int a,b,w;
	int p[100];
	int l;
	while(c!='q') {
		cout<<endl<<"Graph:>";
		cin>>c;
		switch(c) {
			case 'a':
				cin>>a>>b>>w;
				g->AddArc(a,b,w);
				cout<<endl<<"加入了从"<<a<<"到"<<b<<"的弧长为"<<w<<"的弧";
				break;
			case 'p':
				cin>>a>>b;
				l = g->GetShortFloyd(p,100,a,b);
				cout<<endl<<"从"<<a<<"到"<<b<<"的最短路径："<<endl;
				cout<<p[0];
				for(int i=1;i<l;i++)cout<<"-->"<<p[i];
				break;
			case 'l':
				g->PrintArc();
				break;
		}
	}
}
		


		
	
