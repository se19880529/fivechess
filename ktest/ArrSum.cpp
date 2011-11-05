#include "stdafx.h"
#include <iostream>
using namespace std;

int GetSubArr(int arr[], int len, int sub[], int sum) {
	int res = 0;
	if(len<0)return -1;
	else if(len==0){ if(sum==0)return 0; else return -1;}
	else {
		for(int i=0;i<len;i++) {res+=arr[i];}
		if(res<sum)return -1;
		else if(res == sum) {
			if(len<0)return -1;
			for(int i=0;i<len;i++)sub[i] = arr[i];
			return len;
		} else if(sum>0) {
			sub[0] = arr[0];
			res = GetSubArr(&arr[1], len-1, &sub[1], sum-sub[0]);
			if(res>=0) {
				return 1+res;
			} else {
				res = GetSubArr(&arr[1], len-1, sub, sum);
				if(res>=0) return res;
				return -1;
			}
		}
	}
}

void arrsummain() {
	int sum;
	int arr[100];
	int res[100];
	int len=0;
	int size=0;
	char c = 0;
	while(c!='q') {
		cout<<endl<<"求等于和的序列：>";
		cin>>c;
		switch(c) {
			case 'a':
				cin>>arr[len++];
				cout<<endl<<arr[0];
				for(int i=1;i<len;i++)cout<<","<<arr[i];
				break;
			case 'f':
				cin>>sum;
				size = GetSubArr(arr,len, res, sum);
				if(size>0) {
					cout<<endl<<res[0];
					for(int i=1;i<len;i++)cout<<","<<res[i];
				}
				break;
			case 'p':
				for(int i=1;i<len;i++)cout<<","<<arr[i];
				break;
		}
	}
}