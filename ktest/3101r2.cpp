#include "stdafx.h"
#include "timer.h"
#include <iostream>
#include <vector>
#include <string>
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))
using namespace std;
class BigInteger{
public:
	BigInteger();
	BigInteger(const BigInteger&);
	BigInteger(__int64);
	BigInteger(std::string );
	std::string get();
	int CmpNoSign(const BigInteger&) const;
	BigInteger operator-() const;
	int operator[](int i) const {return num[i];}
	BigInteger& operator=(const BigInteger&);
	BigInteger operator+(const BigInteger&) const;
	BigInteger operator-(const BigInteger&) const;
	BigInteger operator*(const BigInteger&) const;
	BigInteger Div(const BigInteger&, BigInteger&) const;
	bool operator<(const BigInteger&) const;
	bool operator>(const BigInteger&) const;
	bool operator==(const BigInteger&) const;
	bool neg;
	std::vector<int> num;
	int wei;
};
typedef BigInteger DaShu;
DaShu GetGCD2(DaShu a1, DaShu a2) {
	DaShu Zero(0);
	DaShu rem(1);
	int remi = 1,a,b;
	while(!(a2 == Zero)) {
		a1.Div(a2,rem);
		a1 = a2;
		a2 = rem;
	}
	return a1;
}
int GetGCD2(int a1,int a2) {
	int gcd = 1,r;
	while(a2) {
		r = a1 % a2;
		a1 = a2;
		a2 = r;
	}
	return a1;
}
void YueFen2(DaShu& fenzi, DaShu& fenmu) {
	DaShu rem;
	DaShu gcd = GetGCD2(fenzi,fenmu);
	fenzi = fenzi.Div(gcd, rem);
	fenmu = fenmu.Div(gcd,rem);
}
void YueFen2(int& fenzi, int& fenmu) {
	int gcd = GetGCD2(fenzi,fenmu);
	fenzi = fenzi/gcd;
	fenmu = fenmu/gcd;
}
DaShu GetLCM(DaShu a, DaShu b) {
	DaShu rem;
	return (a*b).Div(GetGCD2(a,b),rem);
}
void GetLCM(int fenzi[], int fenmu[], int size, DaShu& lcmfenzi, DaShu& lcmfenmu) {
	DaShu* Fenzi = new DaShu[size-1];
	int* Fenmu = new int[size-1];
	DaShu Lcm(0),Max,DaTemp;
	int max = fenzi[0],maxind = 0,ind = 0,fzt,fmt;
	for(int i=0;i<size;i++)if(fenzi[i]>max) {
		max = fenzi[i];
		maxind = i;
	}
	bool same = false;
	Start();
	for(int i=0;i<size;i++) {
		if(fenzi[i] == max)continue;
		same = false;
		for(int j=0;j<ind;j++)if(fenzi[i] == fenzi[j])same = true;
		if(same)continue;
		fzt = fenzi[i]*max;
		fmt = (max-fenzi[i])*2;
		YueFen2(fzt, fmt);
		Fenmu[ind] = fmt;
		Fenzi[ind] = (DaShu)fzt;
		ind++;
	}
	StopCout("均匀周期");
	if(ind==1) {
		lcmfenzi = Fenzi[0];
		lcmfenmu = (DaShu)Fenmu[0];
	} else {
		Start();
		Lcm = GetLCM(Fenzi[0],Fenzi[1]);
		for(int i=2;i<ind;i++) {
			Lcm = GetLCM(Lcm, Fenzi[i]);
		}
		StopCout("计算分子最小公倍数");
		lcmfenzi = Lcm;
		//分母最大公因数
		
		Start();
		max = Fenmu[0];
		for(int i=0;i<ind;i++)if(Fenmu[i]<max)max = Fenmu[i];
		int gcd = 1;bool is = false;
		for(int i=2;i<=max;i++) {
			is = true;
			for(int j=0;j<ind;j++)if( Fenmu[j]%i) { is = false;break;}
			if(is)gcd = i;
		}
		StopCout("分母最大公因数");
		lcmfenmu = (DaShu)gcd;
	}
	YueFen2(lcmfenzi, lcmfenmu);
}
int main3101r2() 
{ 
	int n;
	int fenzi[1000],fenmu[1000];
	cin>>n;
	for(int i=0;i<n;i++) {
		//cin>>fenzi[i];
		fenzi[i] = rand()%9999+1;
	}
	fenzi[0] = 5,fenzi[1] = 3, fenzi[2] = 7;
	DaShu fz,fm;
	GetLCM(fenzi, fenmu, n,fz,fm);
	cout<<fz.get().c_str()<<" "<<fm.get().c_str();
	//cout<<"加："<<DaShu::plus<<"次，减法："<<DaShu::minus<<"次，乘法："<<DaShu::mul<<"次，除法："<<DaShu::div<<"次";
	return 1;
}