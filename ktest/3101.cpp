#include "stdafx.h"
#include <iostream>
#include <string>
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))
using namespace std;

class DaShu {
protected:
	string _buf;
public:
	DaShu():_buf("0"){};
	DaShu(int i);
	DaShu(DaShu&);
	DaShu(string s);

	string invert() const;
	string get() const;
	DaShu operator+(const DaShu& d) const;
	DaShu operator-(const DaShu& d) const;
	DaShu operator*(const DaShu& d) const;
	DaShu Div(const DaShu& d,DaShu& rem) const;
	DaShu& operator=(const DaShu& d);
	bool operator==(const DaShu& d) const;
	bool operator<(const DaShu& d) const;
	bool operator>(const DaShu& d) const;
};
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
	if(*this<d) {
		rem = *this;
		return 0;
	}
	int size = d._buf.length();
	int tail = size;
	int dt;
	string res = "";
	rem = (DaShu)(this->_buf.substr(0,tail));
	if(rem<d) {
		tail++;
		rem = (DaShu)(this->_buf.substr(0,tail));
	}
	DaShu temp;
	while(1) {
		dt = 0;
		temp = (DaShu)"0";
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
		if(tail>=_buf.length())break;
		rem	 = (DaShu)(rem._buf + _buf[tail++]);
		if(rem._buf[0] == '0')rem._buf = rem._buf.substr(1, rem._buf.length()-1);
	}
	return res;
}
DaShu::DaShu(DaShu& d) {
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
	for(int i=0;i<size;i++) {
		temp = a1[i]+a2[i]-'0'-'0' + d;
		res += temp%10+'0';
		d = temp/10;
	}
	for(int i=size;i<a2.length();i++) {
		temp = a2[i]-'0' + d;
		res += temp%10+'0';
		d = temp/10;
	}
	if(d!=0)res = res + char('0'+d);
	return ((DaShu)res).invert();
}
DaShu DaShu::operator -(const DaShu& d) const {
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
	DaShu res(0);
	string temp="",a1 = invert(),a2 = d.invert();
	int temp1,temp2,add;
	for(int i=0;i<a1.length();i++) {
		temp1 = a1[i]-'0';
		temp = "";
		add = 0;
		for(int j = 0;j<a2.length();j++) {
			temp2 = temp1*(a2[j]-'0');
			temp += temp2%10 + '0';
			add = temp2/10;
		}
		while(add>0) {
			temp+= add%10 + '0';
			add = add/10;
		}
		temp = ((DaShu)temp).invert();
		for(int j=0;j<i;j++)temp= temp + '0';
		res = res + ((DaShu)temp);
	}
	return res;
}
void YueFen(DaShu& fenzi, DaShu& fenmu) {
	DaShu flag;
	DaShu fenziyu,fenmuyu;
	DaShu fenzi2,fenmu2;
	DaShu beichu;
	DaShu Zero("0");
	DaShu One("1");
	DaShu Two("2");
	if(fenzi>(DaShu)1 && fenzi>(DaShu)1) {
		bool run = true;
		while(run) {
			flag = MIN(fenmu, fenzi) + One;
			run = false;
			for(DaShu i(Two);i<flag;i = i + One) {
				beichu = (DaShu)i;
				fenmu2 = fenmu.Div(beichu, fenmuyu);
				fenzi2 = fenzi.Div(beichu, fenziyu);
				if( fenmuyu==Zero && fenmuyu == Zero) {
					fenmu = fenmu2,fenzi = fenzi2;
					if(!(fenmu==One || fenzi==One))run = true;
					break;
				}
			}
		}
	}
}
void GetLCM(int fenzi[], int fenmu[], int size, DaShu& lcmfenzi, DaShu& lcmfenmu) {
	DaShu* Fenzi = new DaShu[size];
	DaShu Lcm(0),Max;
	int max = 0;
	for(int i=0;i<size;i++) {
		Fenzi[i] = fenzi[i];
		if(fenzi[i]>max)max = fenzi[i];
	}
	Max = (DaShu)max;
	DaShu rem("1"),Zero("0");
	bool con = true;
	while(con) {
		con = false;
		Lcm = Lcm + Max;
		for(int i=0;i<size;i++) {
			Lcm.Div(Fenzi[i], rem);
			if(!(rem == Zero)) {
				con = true;
				break;
			}
		}
	}
	lcmfenzi = Lcm;
	//分母最大公因数
	max = fenmu[0];
	for(int i=0;i<size;i++) {
		if(fenmu[i]<max)max = fenmu[i];
	}
	int lcmfm = 1;
	for(int j=2;j<=max;j++) {
		con = true;
		for(int i=0;i<size;i++) if(fenmu[i]%j != 0) {con = false;break;}
		if(con)lcmfm = j;
	}
	lcmfenmu = (DaShu)lcmfm;
	YueFen(lcmfenzi, lcmfenmu);
}
	






	




/*
class CFenShu {
public:
	CFenShu();
	CFenShu(int Fenzi, int Fenmu);
	CFenShu(CFenShu& f);
	void YueFen();
	double Get();
	int m_fenmu;
	int m_fenzi;
};
double CFenShu::Get() {
	return ((double)m_fenzi)/((double)m_fenmu);
}
CFenShu::CFenShu():m_fenmu(1),m_fenzi(0){}
CFenShu::CFenShu(int Fenzi, int Fenmu):m_fenmu(Fenmu),m_fenzi(Fenzi) {
	if(m_fenmu==0)m_fenmu=1;
}
CFenShu::CFenShu(CFenShu& f):m_fenmu(f.m_fenmu), m_fenzi(f.m_fenzi){}
void CFenShu::YueFen() {
	int flag;
	if(m_fenmu<=1 || m_fenzi<=1)return;
	bool run = true;
	while(run) {
		flag = MAX(abs(m_fenmu), abs(m_fenzi));
		run = false;
		for(int i=2;i<=flag;i++) {
			if(m_fenmu%i ==0 && m_fenzi%i == 0) {
				m_fenmu/=i,m_fenzi/=i;
				if(m_fenmu!=1 && m_fenzi!=1)run = true;
				break;
			}
		}
	}
}

CFenShu GBS(CFenShu num[], int len) {
	int *temp = new int[len];
	int temp
	double value = num[0].Get(),temp;
	CFenShu tempf;
	int index = 0;
	for(int i=0;i<len;i++)temp[i] = 1;
	bool run = true;
	while(run) {
		run = false;
		tempf.m_fenmu = num[i].m_fenmu, tmepf.m_fenzi=num[i].m_fenzi;
		num[index].indexYueFen();
		for(int i=0;i<len;i++) {
			
			if(run == false && (num[i].m_fenmu != num[0].m_fenmu || num[i].m_fenzi != num[0].m_fenzi))run = true;
		}
		value = num[0].Get();
		index = 0;
		for(int i=0;i<len;i++) {
			if(value>(temp=num[0].Get()))value = temp, index = i;
		}

		
	*/