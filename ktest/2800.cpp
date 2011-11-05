#include "stdafx.h"
#include "timer.h"
#include <iostream>
#include <vector>
#include <conio.h>
#include <string>
#define BASE 10000
#define POW	4
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
BigInteger::BigInteger():wei(1),neg(false) {
	num.push_back(0);
}
BigInteger::BigInteger(const BigInteger &d):wei(d.wei),neg(d.neg) {
	num = d.num;
}
std::string BigInteger::get() {
	char buf[POW+2];std::string r = "";
	if(neg)r = r + "-";
	for(int i=wei-1;i>=0;i--){
		if(i!=wei-1) {
			if(num[i]/1000);
			else if(num[i]/100)r = r+"0";
			else if(num[i]/10)r = r+"00";
			else r = r+"000";
		}
		sprintf(buf,"%d", num[i]);
		r = r + buf;
	}
	return r;
}
BigInteger::BigInteger(std::string c) {
	neg = false;
	while(!c.empty() && (c[0] == '0' || c[0] == ' ' || c[0] == '-')) {
		if(c[0]=='-')neg = !neg;
		c = c.substr(1,c.length()-1);
	}
	if(c.length()==0) {
		wei = 1,neg = false;
		num.push_back(0);
	} else {
		wei = 0;
		int len;
		for(int i=c.length()-1;i>=0;i-=POW) {
			len = (i+1>POW)?POW:(i+1);
			num.push_back(atoi(c.substr(i-len+1, len).c_str()));wei++;
		}
	}
}
BigInteger::BigInteger(__int64 i) {
	wei=0;
	neg = (i<0);
	i = abs(i);
	do {
		num.push_back(i%BASE);
		i/=BASE;
		wei++;
	} while(i>0);
}
BigInteger& BigInteger::operator =(const BigInteger& b) {
	wei = b.wei;
	neg = b.neg;
	num = b.num;return *this;
}
BigInteger BigInteger::operator -() const {
	BigInteger res(*this);
	res.neg = !res.neg;
	return res;
}
bool BigInteger::operator <(const BigInteger& b) const {
	if(b.neg!=neg)
		if(b.neg)return false;else return true;
	return CmpNoSign(b)<0;
}
bool BigInteger::operator >(const BigInteger& b) const {
	if(b.neg!=neg)
		if(b.neg)return true;else return false;
	return CmpNoSign(b)>0;
}
bool BigInteger::operator ==(const BigInteger& b) const {
	if(b.neg!=neg)return false;
	return CmpNoSign(b)==0;
}
int BigInteger::CmpNoSign(const BigInteger& b) const {
	if(wei<b.wei)return -1;else if(wei>b.wei)return 1;else {
		for(int i=wei-1;i>=0;i--)if(num[i]>b.num[i])return 1;else if(num[i]<b.num[i])return -1;
		return 0;
	}
}
BigInteger BigInteger::operator +(const BigInteger &dd) const {
	if(dd.neg!=neg) {							//负数
		if(dd.neg)return *this-(-dd);
		else return dd-(-*this);
	}
	int d=0;
	int as = wei,bs = dd.wei;
	BigInteger a = *this,b = dd;
	if(as<bs){
		as = dd.wei,bs = wei,a = dd, b = *this;
	}
	BigInteger res(a);int temp;
	for(int i=0;i<bs;i++) {
		temp = a[i] + b[i] + d;
		res.num[i] = temp%BASE;
		d = temp/BASE;
	}
	for(int i=bs;i<as;i++) {
		temp = a[i]+d;
		res.num[i] = temp%BASE;
		d = temp/BASE;
		if(d==0)break;
	}
	if(d!=0) {
		res.num.push_back(d);
		res.wei++;
	}
	while(res.wei>1 && res.num.back() == 0  ){res.num.pop_back();res.wei--;}
	res.neg = neg;
	return res;
}
BigInteger BigInteger::operator -(const BigInteger &dd) const {
	if(dd.neg!=neg) return *this+(-dd);								//负数
	int i,temp,d=0;
	BigInteger a,b,res;
	res.num.clear(),res.wei = 0;
	if(dd>*this){a=dd,b=*this,res.neg=true;}
	else if(dd==*this) return 0;
	else {a=*this, b=dd,res.neg=false;};
	for(i=0;i<b.wei;i++){
		temp = a.num[i]+BASE-b.num[i]-d;
		if(temp>=BASE) temp-=BASE,d=0;
		else d = 1;
		res.num.push_back(temp);res.wei++;
	}
	while(d>0) {
		if(a[i]>=d)temp = a.num[i]-d,d=0;
		else temp=a.num[i]+BASE-d,d=1;
		res.num.push_back(temp);res.wei++;i++;
	}
	for(;i<a.wei;i++){res.num.push_back(a.num[i]);res.wei++;};
	while(res.wei>1 && res.num.back() == 0  ){res.num.pop_back();res.wei--;}
	if(neg)res.neg = !res.neg;
	return res;
}
BigInteger BigInteger::operator *(const BigInteger &d) const {
	int temp,dd=0;
	BigInteger res,tempb;
	if((d.num[0]==0 && d.wei==1) || (num[0]==0 && wei==1))return 0;
	for(int i=0;i<d.wei;i++) {
		if(d[i]==0)tempb = 0;
		else {
			tempb.num.clear();
			tempb.wei=0;dd=0;
			for(int j=0;j<i;j++){tempb.num.push_back(0);tempb.wei++;}
			for(int j=0;j<wei;j++) {
				temp = d[i]*num[j] + dd;
				tempb.num.push_back(temp%BASE);tempb.wei++;
				dd = temp/BASE;
			}
			if(dd>0){tempb.num.push_back(dd);tempb.wei++;}
		}
		res = res + tempb;
	}
	if(neg == d.neg)res.neg = false;
	else res.neg = true;
	while(res.wei>1 && res.num.back() == 0  ){res.num.pop_back();res.wei--;}
	return res;
}
BigInteger BigInteger::Div(const BigInteger & dat, BigInteger & rem) const {
	int low,high,mid,tail;rem.num.clear();rem.wei=0;BigInteger res;res.num.clear();res.wei=0;
	if(CmpNoSign(dat)<0) { rem = *this;return 0;}
	BigInteger data(dat);data.neg=false;
	tail = data.wei;rem.wei=tail;
	for(int i=0;i<tail;i++)rem.num.insert(rem.num.begin(), num[wei-i-1]);
	if(rem.CmpNoSign(data)<0){tail++, rem.num.insert(rem.num.begin(),num[wei-tail]);rem.wei = tail;}
	while(1) {
		if(rem.CmpNoSign(data)<0) {
			low = 0;
		} else {
			low = 1,high = BASE-1;
			while(low<high){ mid = (low+high+1)/2;if((data*(BigInteger)mid).CmpNoSign(rem)>0)high=mid-1;else low = mid;}
			rem = rem-data*(BigInteger)low;
		}
		res.num.insert(res.num.begin(),low);res.wei++;
		if(tail>=wei)break;
		tail++;
		rem.num.insert(rem.num.begin(), num[wei-tail]);rem.wei++;
	}
	if(dat.neg!=neg)res.neg = true;
	while(res.wei>1 && res.num.back() == 0  ){res.num.pop_back();res.wei--;}
	return res;
}
__int64 GetSum(int n,int k) {
	__int64 sum=0;
	for(int i=1;i<n;i++)sum+=k%i;
	return sum;
}
int main2800() {
	using namespace std;
	BigInteger rem;
	string n="";char nc=1;
	int k;__int64 resi=0;
	cin>>nc;
	while(nc!=' ' && nc !='\n') {
		n = n + nc;
		nc = cin.get();
	}
	cin>>k;
	Start();
	BigInteger a(n),b(k);
	StopCout("转换为数字");
	Start();
	int size = k;if(a<(BigInteger)size)size = atoi(n.c_str());
	for(int i=1;i<=size;i++)resi=resi+(__int64)(k%i);
	StopCout("求变化的和");
	BigInteger res(resi);
	Start();
	if(a>(BigInteger)k)res = res + (BigInteger)k*(BigInteger)(a-k);
	StopCout("求乘法");
	cout<<res.get();
	return 0;
}