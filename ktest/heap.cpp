#include "stdafx.h"
#include <iostream>
using namespace std;
template<class Type>
class Heap {
private:
	Type* m_Buffer;
	int m_iMaxSize;
	int m_iSize;
public:
	int GetSize() {return m_iSize;}
	Type& operator[](int i) { return m_Buffer[i];}
	Heap(int n);
	int ShiftUp(int ind);
	int ShiftDown(int ind);
	int Insert(const Type& t);
	int Delete(int ind);
	Type& GetRoot();
};
template<typename Type>
Heap<Type>::Heap(int n) {
	m_iMaxSize = n;
	m_iSize = 0;
	m_Buffer = new Type[n];
}
template<typename Type>
int Heap<Type>::ShiftUp(int ind) {
	int i = ind/2,j=ind;
	Type t = m_Buffer[ind];
	while(i>0) {
		if(m_Buffer[i] < t) {
			m_Buffer[j] = m_Buffer[i];
			j = i;i = i/2;
		} else break;
	}
	m_Buffer[j] = t;
	return j;
}
template<typename Type>
int Heap<Type>::ShiftDown(int ind) {
	int i = ind,j = ind*2;
	Type t = m_Buffer[ind];
	while(j<=m_iSize) {
		if(j+1<=m_iSize && m_Buffer[j+1]>m_Buffer[j])j++;
		if(m_Buffer[j]>t)m_Buffer[i] = m_Buffer[j]; else break;
		i = j;j=j*2;
	}
	m_Buffer[i] = t;
	return i;
}
template<typename Type>
int Heap<Type>::Insert(const Type& t) {
	if(m_iSize<m_iMaxSize) {
		m_Buffer[++m_iSize] = t;
		return	ShiftUp(m_iSize);
	}
	return -1;
}
template<typename Type>
int Heap<Type>::Delete(int ind) {
	m_Buffer[ind] =m_Buffer[m_iSize--];
	return	ShiftDown(ind);

}
template<typename Type>
Type& Heap<Type>::GetRoot() {
	return m_Buffer[1];
}


typedef Heap<int> heap;


void mainheap() {
	heap Hp(1000);
	char cmd;
	int i;
	while(1)
	{
		cout<<"?>";
		cin>>cmd;
		cin>>i;
		if(cmd == 'i') {
			Hp.Insert(i);
		} else if(cmd == 'd') {
			Hp.Delete(i);
		} else if(cmd == 'r') {
			cout<<endl<<Hp.GetRoot();
		} else if(cmd == 'q') {
			break;
		}
		cout<<endl<<"After operation Heap is:{";
		if(Hp.GetSize()>0) {
			cout<<"1:"<<Hp[1];
			for(int i=2;i<=Hp.GetSize();i++) {
				cout<<","<<i<<":"<<Hp[i];
			}
		}
		cout<<"}"<<endl;
	}
}