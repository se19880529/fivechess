#include "stdafx.h"
#include <stdio.h>
char* CompressSpace(char str[]) {
	int len = strlen(str);
	int len1,p=0,p2;
	for(p=0;p<len;p++) {
		if(str[p] == ' ') {
			for(len1=0;str[len1+p]==' ';len1++);								//计算空格数目
			if(len1>1)for(p2=p+len1;p2<=len;p2++)str[p2-len1+1] = str[p2];		//消除多于1个的空格
			len-=len1-1;
		}
	}
	return str;
}

void baidu1027test() {
	char str[1000];
	while(1) {
		scanf("%[^\n]s", str);
		getchar();
		printf("\n{%s}\n",CompressSpace(str));
	}
}