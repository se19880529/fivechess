#include "stdafx.h"
#include <iostream>
using namespace std;
/*
template <class type>
int Partition(type arr[], int s,int t) {
	type flag = arr[s];
	int b = ++s,e = t;
	while(s<t) {
		while(arr[s]<flag && s<=e)s++;
		while(arr[t]>=flag && t>=b)t--;
		if(s<t) {
			type temp = arr[s];
			arr[s] = arr[t];
			arr[t] = temp;
		}
	}
	type temp = arr[s-1];
	arr[s-1] = arr[b-1];
	arr[b-1] = temp;
	return s-1;
}
template <class type>
void QuickSort(type arr[], int s,int t) {
	if(s<t) {
		int f = Partition(arr,s,t);
		QuickSort(arr, s,f-1);
		QuickSort(arr, f+1, t);
	}
}
*/
/*Ωªªª*/
template <class elem_t>
void Swap(elem_t &a, elem_t &b) {
	elem_t t = a;
	a = b;
	b = t;
}
/*øÏÀŸ≈≈–Ú*/
template <class elem_t>
int Partition(elem_t arr[], int lo, int hi) {
	int i=lo+1,j=hi-1;
	elem_t e,flag = arr[lo];
	while(i<j) {
		while(i<hi && arr[i]<=flag)i++;
		while(j>=0 && arr[j]>flag)j--;
		if(i<j) {
			e = arr[i];
			arr[i] = arr[j];
			arr[j] = e;
		}
	}
	arr[lo] = arr[i-1];
	arr[i-1] = flag;
	return i-1;
}
template <class elem_t>
void QuickSort(elem_t arr[], int lo, int hi) {
	if(lo<hi) {
		int ind = Partition(arr,lo,hi);
		QuickSort(arr, lo, ind);
		QuickSort(arr, ind+1, hi);
	}
}
/*∂—≈≈–Ú(◊Ó¥Û∂—)*/
template <class elem_t>
void HeapAdjust(elem_t arr[],int n, int i) {
	elem_t e;int j=i*2;
	while(j<=n) {
		if(j+1<=n && arr[j+1]>arr[j])j++;
		if(arr[j]>arr[i]) {
			e = arr[i];
			arr[i] = arr[j];
			arr[j] = e;
		} else break;
		i=j;j = i*2;
	}
}
template <class elem_t>
void MakeHeap(elem_t arr[], int n) {
	arr[n] = arr[0];
	for(int i=n/2;i>=1;i--)HeapAdjust(arr,n,i);
}
template <class elem_t>
void HeapSort(elem_t arr[], int n) {
	MakeHeap(arr,n);
	elem_t e;
	for(int i=n;i>=2;i--) {
		e = arr[1];
		arr[1] = arr[i];
		arr[i] = e;
		HeapAdjust(arr,i-1,1);
	}
}
/*πÈ≤¢≈≈–Ú*/
#define MAXMERGE	1000
template <class elem_t>
void Merge(elem_t arr[], int s,int m,int t) {
	static  elem_t temparr[MAXMERGE];
	if(s<t) {
		int i = s,j = m+1,p=0;
		while(i<=m && j<=t) {
			if(arr[i]<=arr[j])temparr[p++] = arr[i++];
			else temparr[p++] = arr[j++];
		}
		while(i<=m)temparr[p++] = arr[i++];
		while(j<=t)temparr[p++] = arr[j++];
		for(i=0;i<p;i++)arr[s+i] = temparr[i];
	}
}
template <class elem_t>
void MergeSort(elem_t arr[], int s,int t) {
	if(s<t) {
		int ind = s+(t-s)/2;
		MergeSort(arr, s, ind);
		MergeSort(arr, ind+1, t);
		Merge(arr, s, ind, t);
	}
}
/*œ£∂˚≈≈–Ú*/
template <class elem_t>
void StepInsertSort(elem_t arr[], int d, int s, int t) {
	if(t>s) {
		int end = s + ((t-s)/d)*d;
		for(int i=s+d;i<=end;i+=d) {
			int flag = arr[i],j;
			for(j=i-d;j>=s && arr[j]>flag;j-=d)arr[j+d] = arr[j];
			arr[j+d] = flag;
		}
	}
}
template <class elem_t>
void ShellSort(elem_t arr[], int n) {
	int mstep;
	for(mstep=1;mstep*3+1<n;mstep=mstep*3+1);
	for(;mstep>=1;mstep = (mstep-1)/3)
		for(int i=0;i<mstep;i++)
			StepInsertSort(arr, mstep, i, n-1);
}

void mainquicksort() {
	char c[1000];
	while(1) {
		cout<<endl<<"qsort:>";
		cin>>c;
		c[strlen(c)+1] = 0;
		ShellSort(c, strlen(c));
		cout<<endl<<"reault:"<<c;
	}
}