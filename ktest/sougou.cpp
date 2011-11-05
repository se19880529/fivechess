#include "stdafx.h"
#include <stdio.h>
#include <iostream>
using namespace std;
  
int GetL(int arr[], int n) {
	int *temparr = new int[n],res=0;
	for(int i=0;i<n;i++)temparr[i] = 1;
	for(int i=0;i<n;i++) {
		int temp = arr[i],max=0;
		for(int j=0;j<i;j++) {
			if(arr[j]<temp && temparr[j]>max)max = temparr[j];
		}
		temparr[i]+=max;
		if(temparr[i]>res)res = temparr[i];
	}
	return res;
}


int mainsougou()
{
     int len=0,arr[1000];
	 do {
		 cin>>arr[len];
	 }while(arr[len++]!=0);
	 cout<<endl<<GetL(arr,len);
	 return 0;
} 