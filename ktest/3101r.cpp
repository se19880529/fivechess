#include "stdafx.h"
#include "timer.h"
#include <iostream>
#include <string>
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))
using namespace std;

class DaShu {
protected:
	string _buf;
public:
	static int plus,minus,div,mul;
	DaShu():_buf("0"){};
	DaShu(int i);
	DaShu(const DaShu&);
	DaShu(string s);
	string invert() const;
	string get() const;
	DaShu operator+(const DaShu& d) const;
	DaShu operator-(const DaShu& d) const;
	DaShu operator*(const DaShu& d) const;
	DaShu Div(const DaShu& d,DaShu& rem) const;
	DaShu& operator=(const DaShu& d);
	DaShu& operator=(const string s) {_buf = s; return *this;}
	bool operator==(const DaShu& d) const;
	bool operator<(const DaShu& d) const;
	bool operator>(const DaShu& d) const;
};
int DaShu::plus = 0;
int DaShu::minus = 0;
int DaShu::div = 0;
int DaShu::mul = 0;
DaShu Zero(0),IntMax("2147483647");
int pow[8] = {10,100,1000,10000,100000,1000000,10000000,100000000};
bool DaShu::operator==(const DaShu& d) const {
	return d._buf.compare(_buf)==0;
}
string DaShu::get() const {
	return _buf;
}
string DaShu::invert() const {
	string res="";
	for(int i=_buf.length()-1;i>=0;i--)res = res + _buf[i];
	return res;
}

bool DaShu::operator <(const DaShu& d) const {
	if(d._buf.length()>_buf.length())return true;
	if(d._buf.length()==_buf.length() && d._buf.compare(_buf)==1)return true;
	return false;
}

bool DaShu::operator >(const DaShu& d) const {
	if(d._buf.length()<_buf.length())return true;
	if(d._buf.length()==_buf.length() && d._buf.compare(_buf)==-1)return true;
	return false;
}

DaShu::DaShu(int i) {
	char buf[16];
	sprintf(buf,"%d", i);
	_buf = buf;
}
DaShu DaShu::Div(const DaShu &d, DaShu& rem) const {
	//Start();
	bool f = false;
	if(d<IntMax)f = true;
	div++;
	if(*this<d) {
		rem = *this;
		return 0;
	}
	if(*this<IntMax) {
		int a = atoi(_buf.c_str()),b = atoi(d._buf.c_str());
		rem = a%b;
		//StopCout("除法");
		return a/b;
	}
	int size = d._buf.length();
	int tail = size;
	int dt;
	string res = "";
	rem = this->_buf.substr(0,tail);
	if(rem<d) {
		tail++;
		rem = this->_buf.substr(0,tail);
	}
	DaShu temp;
	int tempa,tempb;
	while(1) {
		dt = 0;
		if(rem<IntMax && f) {
			tempa = atoi(rem.get().c_str()), tempb = atoi(d.get().c_str());
			dt = tempa/tempb;
			res = res + (char)(dt + '0');
			rem = (DaShu)(tempa%tempb);
		} else {
			temp = "0";
			while(1) {
				if(temp + d>rem) {
					rem = rem-temp;
					res = res + (char)(dt + '0');
					break;
				} else {
					temp = temp + d;
					dt++;
				}
			}
		}
		if(tail>=_buf.length())break;
		rem	 = (DaShu)(rem._buf + _buf[tail++]);
		if(rem._buf[0] == '0')rem._buf = rem._buf.substr(1, rem._buf.length()-1);
	}
	//StopCout("除法");
	return res;
}
DaShu::DaShu(const DaShu& d) {
	_buf = d._buf;
}
DaShu::DaShu(std::string s) {
	_buf = s;
}
DaShu& DaShu::operator =(const DaShu& d) {
	_buf = d._buf;
	return *this;
}
DaShu DaShu::operator +(const DaShu &dd) const {
	plus++;
	//Start();
	int d;
	string a1,a2,res = "";
	int size;
	if(dd._buf.length()>_buf.length()) {
		a1 = invert();
		a2 = dd.invert();
		size = a1.length();
	} else {
		a1 = dd.invert();
		a2 = invert();
		size = a1.length();
	}
	d = 0;
	int temp;
	res = a2;
	for(int i=0;i<size;i++) {
		temp = a1[i]+a2[i]-'0'-'0' + d;
		res[i] = temp%10+'0';
		d = temp/10;
	}
	for(int i=size;i<a2.length();i++) {
		temp = a2[i]-'0' + d;
		res[i] = temp%10+'0';
		d = temp/10;
		if(d==0)break;
	}
	if(d!=0)res = res + char('0'+d);
	//StopCout("加法");
	return ((DaShu)res).invert();
}
DaShu DaShu::operator -(const DaShu& d) const {
	minus++;
	DaShu a,b;
	int asize,bsize,size;
	if(d>*this)a = d,b=*this;
	else a=*this,b=d;
	asize = a._buf.length();
	bsize = b._buf.length();
	if(asize>bsize)size = bsize;
	else size = asize;
	string aa = a.invert(),bb = b.invert(),res;
	int borrow = 0;
	char temp = 0;
	res = "";
	for(int i=0;i<size;i++) {
		temp = aa[i]-borrow+10-bb[i];
		borrow = 0;
		if(temp>=10)temp=temp-10+'0';else temp=temp+'0',borrow = 1;
		res = res + temp;
	}
	for(int i=size;i<aa.size();i++) {
		temp = aa[i]-borrow+10-'0';
		borrow = 0;
		if(temp>=10)temp=temp-10+'0';else temp=temp+'0',borrow = 1;
		res = res + temp;
	}
	res = ((DaShu)res).invert();
	while(res[0]<='0' && res.length()>1)res = res.substr(1,res.length()-1);
	return res;
}
DaShu DaShu::operator *(const DaShu &d) const {
	mul++;
	//Start();
	DaShu res(0);
	string temp="",a1,a2;
	if(_buf.length()>d._buf.length()) {
		a1 = d.invert();
		a2 = _buf;
	} else {
		a1 = invert();
		a2 = d._buf;
	}
	int len,temp1,temp2,add;
	for(int i=0;i<a1.length();i++) {
		temp1 = a1[i]-'0';
		temp = "";
		add = 0;
		for(int j = a2.length()-1;j>=0;j-=8) {
			len = j+1;
			if(len>8)len=8;
			temp2 = temp1*atoi(a2.substr(j+1-len, len).c_str())+add;
			temp += ((DaShu)(temp2%(pow[len-1]))).invert();
			add = temp2/(pow[len-1]);
		}
		while(add>0) {
			temp+= add%10 + '0';
			add = add/10;
		}
		temp = ((DaShu)temp).invert();
		for(int j=0;j<i;j++)temp= temp + '0';
		res = res + ((DaShu)temp);
	}
	//StopCout("乘法");
	return res;
}
DaShu GetGCD(DaShu a1, DaShu a2) {
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
int GetGCD(int a1,int a2) {
	int gcd = 1,r;
	while(a2) {
		r = a1 % a2;
		a1 = a2;
		a2 = r;
	}
	return a1;
}
void YueFen(DaShu& fenzi, DaShu& fenmu) {
	DaShu rem;
	DaShu gcd = GetGCD(fenzi,fenmu);
	fenzi = fenzi.Div(gcd, rem);
	fenmu = fenmu.Div(gcd,rem);
}
void YueFen(int& fenzi, int& fenmu) {
	int gcd = GetGCD(fenzi,fenmu);
	fenzi = fenzi/gcd;
	fenmu = fenmu/gcd;
}
DaShu GetLCM(DaShu a, DaShu b) {
	DaShu rem;
	return (a*b).Div(GetGCD(a,b),rem);
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
		YueFen(fzt, fmt);
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
	YueFen(lcmfenzi, lcmfenmu);
}
int __main() 
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