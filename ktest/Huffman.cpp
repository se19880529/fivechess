#include "stdafx.h"
#include <iostream>
#include <vector>
#define INTMAX 0x7FFFFFFF
using namespace std;
class Byte {
protected:
	char buffer[128];
	int m_iSize;
public:
	int GetSize() { return m_iSize;}
	Byte(Byte& b):m_iSize(b.m_iSize){
		int i;
		for(i=0;i<((m_iSize+8)>>3);i++)
			buffer[i] = b.buffer[i];
	};	
	Byte():m_iSize(0){};
	Byte& operator=(Byte& b) { 
		m_iSize = b.m_iSize;
		for(int i=0;i<((m_iSize+8)<<3);i++)
			buffer[i] = b.buffer[i];
	};
	void Push(int i) {
		int mask = 1<<(m_iSize%8);
		if(i)buffer[m_iSize/8] |= mask;
		else buffer[m_iSize/8] &= ~mask;
		m_iSize++;
	}
	int Look() {
		if(m_iSize==0)return -1;
		int mask = 1<<((m_iSize-1)%8);
		mask = mask & buffer[(m_iSize-1)/8];
		mask = mask>>((m_iSize-1)%8);
		return mask;
	}
	int Pop() {
		if(m_iSize==0)return -1;
		int mask = 1<<((m_iSize-1)%8);
		mask = mask & buffer[(m_iSize-1)/8];
		mask = mask>>((m_iSize-1)%8);
		m_iSize--;
		return mask;
	}
	void Print() {
		if(m_iSize==0)cout<<"NaN";
		else {
			for(int i=0;i<m_iSize;i++) {
				cout<<((buffer[i/8]>>(i%8))&1);
			}
		}
	}
};


template <class Type>
class Huffman {
public:
	typedef Type elem_t;
	struct Node{
		elem_t value;
		int weight;
		int parent;
		int lchild;
		int rchild;
	};
	Huffman(int n);
	~Huffman(){delete[] m_nBuffer;}
	void Reset(int[], elem_t[]);
protected:
	Node* m_nBuffer;
	int m_iSize;
	int m_iNum;
};
template <class T>
Huffman<T>::Huffman(int n):m_iSize(2*n-1),m_iNum(n) {
	m_nBuffer = new Node[m_iSize+1];
}
template <class T>
void Huffman<T>::Reset(int w[], elem_t e[]) {
	int len = m_iNum;
	for(int i=1;i<=m_iNum;i++) {
		m_nBuffer[i].value = e[i-1];
		m_nBuffer[i].lchild = 0;
		m_nBuffer[i].rchild = 0;
		m_nBuffer[i].parent = 0;
		m_nBuffer[i].weight = w[i-1];
	}
	int s1=INTMAX,s2=INTMAX,m1 = INTMAX,m2 = INTMAX;
	while(1) {
		s1=INTMAX,s2=INTMAX,m1 = INTMAX,m2 = INTMAX;
		for(int i=1;i<=len;i++) {
			if(m_nBuffer[i].parent==0) {
				if(m_nBuffer[i].weight<m1) {
					s2 = s1,m2 = m1;
					s1 = i,m1 = m_nBuffer[i].weight;
				} else if(m_nBuffer[i].weight<m2) {
					s2 = i;
					m2 = m_nBuffer[i].weight;
				}
			}
		}
		if(s2 == INTMAX || len>=m_iSize)break;
		len++;
		m_nBuffer[len].lchild = s1;
		m_nBuffer[s1].parent = len;
		m_nBuffer[s2].parent = len;
		m_nBuffer[len].rchild = s2;
		m_nBuffer[len].parent = 0;
		m_nBuffer[len].weight = m1+m2;
	}
}
class StringHuffman:public Huffman<char> {
public:
	StringHuffman():Huffman(256){};
	Byte CodeString(char str[], int len) {
		int *count = new int[256];
		char *alpha = new char[256];
		memset(count,0,256*sizeof(int));
		for(int i=0;i<len;i++) {
			count[str[i]]++;
		}
		for(int i=0;i<256;i++)alpha[i] = i;
		Reset(count, alpha);
		Byte res;
		for(int i=0;i<len;i++) {
			int p = str[i] + 1,pare;
			while(m_nBuffer[p].parent!=0) {
				pare = m_nBuffer[p].parent;
				if(m_nBuffer[pare].lchild == p) res.Push(0);
				else res.Push(1);
				p = pare;
			}
		}
		for(int i=0;i<256;i++) {
			if(count[i]==0)continue;
			int p = i + 1,pare;
			cout<<"'"<<(char)(p-1)<<"':";
			Byte temp;
			while(m_nBuffer[p].parent!=0) {
				pare = m_nBuffer[p].parent;
				if(m_nBuffer[pare].lchild == p) temp.Push(0);
				else temp.Push(1);
				p = pare;
			}
			temp.Print();
			cout<<" ";
		}
		cout<<endl;
		return res;
	}
	int DecodeString(Byte b,char str[],int len) {
		int l = 0;
		int p;
		while(b.GetSize()!=0) {
			p = m_iSize;
			while(m_nBuffer[p].lchild!=0) {
				int t = b.Pop();
				if(t == 1)p = m_nBuffer[p].rchild;
				else p = m_nBuffer[p].lchild;
			}
			if(len>l+1) {
				str[l++] = m_nBuffer[p].value;
			}
		}
		if(len>l) {
			for(int i=0;i<l/2;i++) {
				char temp = str[i];
				str[i] = str[l-i-1];
				str[l-i-1] = temp;
			}
		}
		str[l] = 0;
		return l;
	}
};
void mainhuffman() {
	StringHuffman sh;
	while(1) {
		char word[100];
		int l;
		cout<<"Huffman:>";
		cin>>word;
		cout<<endl;
		Byte b = sh.CodeString(word,l=strlen(word));
		cout<<endl<<"结果是：";b.Print();
		cout<<"共"<<b.GetSize()<<"位";
		cout<<endl<<"原码为"<<8*l<<"位,压缩率："<<b.GetSize()*100/(8*l)<<"%";
		sh.DecodeString(b,word, 100);
		cout<<endl<<"解码后得到："<<word;
		cout<<endl;
	}
}