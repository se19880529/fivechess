#include "stdafx.h"
#include "timer.h"
#include <iostream>
using namespace std;
#define INTMAX 0x7FFFFFFF
#define DISTANCE	2
#define DEFENCE 2
class QiPan{
public:
	QiPan(int);
	~QiPan();
	void Init();
	void SetChess(int x,int y, int c);
	void ClearChess(int x,int y);
	int GetChess(int x,int y);
	int GetNear(int x,int y);
	void Print();
	int GetSize() { return m_iSize;}
protected:
	int* m_iBuffer;
	short* m_iNear;
	int m_iSize;
};
QiPan::QiPan(int i):m_iSize(i) {
	m_iBuffer = new int[m_iSize*m_iSize];
	m_iNear = new short[m_iSize*m_iSize];
	memset(m_iBuffer, 0, m_iSize*m_iSize*sizeof(int));
	memset(m_iNear,0,m_iSize*m_iSize*sizeof(short));
};
void QiPan::Print() {
	cout<<endl<<"   ";
	for(int i=0;i<m_iSize;i++) {
		if(i<10)cout<<" ";
		cout<<i;
	}
	for(int i=0;i<m_iSize;i++) {
		cout<<endl;
		if(i<10)cout<<" ";
		cout<<i<<" ";
		for(int j=0;j<m_iSize;j++)
			if(m_iBuffer[i*m_iSize+j] <0) cout<<" X"; else if(m_iBuffer[i*m_iSize+j]>0) cout<<" O"; else cout<<" _";
	}
	cout<<endl;
}
QiPan::~QiPan() {delete[] m_iBuffer;}
void QiPan::ClearChess(int x, int y) {
	m_iBuffer[y*m_iSize+x] = 0;
	int temp;
	for(int i=1;i<DISTANCE;i++){
		if((temp=y*m_iSize+(x+i))>=0)m_iNear[temp]--;
		if((temp=y*m_iSize+(x-i))>=0)m_iNear[temp]--;
		if((temp=(y+i)*m_iSize+(x))>=0)m_iNear[temp]--;
		if((temp=(y-i)*m_iSize+(x))>=0)m_iNear[temp]--;
		if((temp=(y+i)*m_iSize+(x+i))>=0)m_iNear[temp]--;
		if((temp=(y-i)*m_iSize+(x+i))>=0)m_iNear[temp]--;
		if((temp=(y+i)*m_iSize+(x+i))>=0)m_iNear[temp]--;
		if((temp=(y-i)*m_iSize+(x+i))>=0)m_iNear[temp]--;
	}
}
void QiPan::SetChess(int x, int y, int c) {
	m_iBuffer[y*m_iSize+x] = c;
	int temp;
	for(int i=1;i<DISTANCE;i++){
		if((temp=y*m_iSize+(x+i))>=0)m_iNear[temp]++;
		if((temp=y*m_iSize+(x-i))>=0)m_iNear[temp]++;
		if((temp=(y+i)*m_iSize+(x))>=0)m_iNear[temp]++;
		if((temp=(y-i)*m_iSize+(x))>=0)m_iNear[temp]++;
		if((temp=(y+i)*m_iSize+(x+i))>=0)m_iNear[temp]++;
		if((temp=(y-i)*m_iSize+(x+i))>=0)m_iNear[temp]++;
		if((temp=(y+i)*m_iSize+(x+i))>=0)m_iNear[temp]++;
		if((temp=(y
			-i)*m_iSize+(x+i))>=0)m_iNear[temp]++;
	}
}
int QiPan::GetNear(int x,int y) {return m_iNear[y*m_iSize+x];}
int QiPan::GetChess(int x,int y) { return m_iBuffer[y*m_iSize+x];}
void QiPan::Init() {memcpy(m_iBuffer, 0, m_iSize*m_iSize*sizeof(int));}
#define PATTERN_LEN	8
#define PATTERN_NUM	9
int g_pattern[PATTERN_NUM][PATTERN_LEN] = {
	{2,-1,-1,-1,-1,-1,2,2},					//赢
	{0,-1,-1,-1,-1,0,2,2},					//活4
	{2,-1,-1,-1,-1,0,2,2},					//冲4
	{0,-1,-1,-1,-1,2,2,2},					//冲4
	{0,-1,-1,-1,0,2,2,2},					//活3
	{2,-1,-1,-1,0,2,2,2},					//冲3
	{0,-1,-1,0,2,2,2,2},					//活2
	{2,-1,-1,0,2,2,2,2},					//冲2
	{0,-1,0,2,2,2,2,2},
};		//模式
int g_pattern_v[PATTERN_NUM] = { 
	1000000,
	100000,
	4000,
	2000,
	150,
	20,
	20,
	5,
	5
};
bool Pattern(int pt[], int me[], bool isme)	{							//pattern应该具有8个元素
	int m = 1;
	if(isme==false)m = -1;
	for(int i=0;i<PATTERN_LEN;i++) {
		if(pt[i]!=m*me[i] &&
			pt[i]!=2)		return false;
	}
	return true;
}
int WritePattern(int p[], QiPan& q, int x, int y, int dx, int dy) {
	int me = q.GetChess(x,y);
	x-=dx,y-=dy;
	int sp=0;
	int dec = 0;
	bool start = false,nocount=false,lastsp=false;;
	for(int i=0;i<PATTERN_LEN;i++) {
		if(x<0 || x>=q.GetSize() || y<0 || y>=q.GetSize()) {
			p[i] = -me;
		} else {
			if(!nocount)dec++;
			p[i] = q.GetChess(x,y);
			if(p[i] == me) start = true,lastsp = false;
			else if(p[i]==0){sp++; if(lastsp)nocount=true; lastsp=true;}
			else if(p[i] == -me && start) nocount=true,lastsp=false;
		}
		x+=dx,y+=dy;
	}
	return dec-1;
}
int vt = 0;
int ValueOf(QiPan& p) {
	int pt[8];
	int value=0;
	int dx,dy,x,y,sx,sy;
	int dec;
	vt++;
	//Start();
	//横向搜索
	dx = 1,dy = 0;
	for(y = 0;y<p.GetSize();y++) {
		x = 0;
		while(x<p.GetSize()) {
			if(p.GetChess(x,y)==-1) {
				dec = WritePattern(pt,p,x,y,dx,dy);
				for(int i=0;i<PATTERN_NUM;i++)if(Pattern(g_pattern[i],pt,true)){value+=g_pattern_v[i];break;}
				x += dec*dx;
			}
			x+=dx;
		}
	}
	//搜索反
	dx = 1,dy = 0;
	for(y = 0;y<p.GetSize();y++) {
		x = 0;
		while(x<p.GetSize()) {
			if(p.GetChess(x,y)==1) {
				dec = WritePattern(pt,p,x,y,dx,dy);
				for(int i=0;i<PATTERN_NUM;i++)if(Pattern(g_pattern[i],pt,false)){value-=DEFENCE*g_pattern_v[i];break;}
				x += dec*dx;
			}
			x+=dx;
		}
	}
	//纵向搜索
	dx = 0,dy = 1;
	for(x = 0;x<p.GetSize();x++) {
		y = 0;
		while(y<p.GetSize()) {
			if(p.GetChess(x,y)==-1) {
				dec = WritePattern(pt,p,x,y,dx,dy);
				for(int i=0;i<PATTERN_NUM;i++)if(Pattern(g_pattern[i],pt,true)){value+=g_pattern_v[i];break;}
				y += dec*dy;
			}
			y+=dy;
		}
	}
	dx = 0,dy = 1;
	for(x = 0;x<p.GetSize();x++) {
		y = 0;
		while(y<p.GetSize()) {
			if(p.GetChess(x,y)==1) {
				dec = WritePattern(pt,p,x,y,dx,dy);
				for(int i=0;i<PATTERN_NUM;i++)if(Pattern(g_pattern[i],pt,false)){value-=DEFENCE*g_pattern_v[i];break;}
				y += dec*dy;
			}
			y+=dy;
		}
	}
	//右下搜索
	dx = 1,dy = 1;
	for(sy = 0;sy<p.GetSize();sy++) {
		x = 0;
		for(y=sy;y<p.GetSize();) {
			if(p.GetChess(x,y)==-1) {
				dec = WritePattern(pt,p,x,y,dx,dy);
				for(int i=0;i<PATTERN_NUM;i++)if(Pattern(g_pattern[i],pt,true)){value+=g_pattern_v[i];break;}
				y += dec*dy;
				x+dec*dx;
			}
			y+=dy,x+=dx;
		}
	}
	for(sx = 1;sx<p.GetSize();sx++) {
		y = 0;
		for(x=sx;x<p.GetSize();) {
			if(p.GetChess(x,y)==-1) {
				dec = WritePattern(pt,p,x,y,dx,dy);
				for(int i=0;i<PATTERN_NUM;i++)if(Pattern(g_pattern[i],pt,true)){value+=g_pattern_v[i];break;}
				y += dec*dy;
				x+dec*dx;
			}
			y+=dy,x+=dx;
		}
	}
	for(sy = 0;sy<p.GetSize();sy++) {
		x = 0;
		for(y=sy;y<p.GetSize();) {
			if(p.GetChess(x,y)==1) {
				dec = WritePattern(pt,p,x,y,dx,dy);
				for(int i=0;i<PATTERN_NUM;i++)if(Pattern(g_pattern[i],pt,false)){value-=DEFENCE*g_pattern_v[i];break;}
				y += dec*dy;
				x+dec*dx;
			}
			y+=dy,x+=dx;
		}
	}
	for(sx = 1;sx<p.GetSize();sx++) {
		y = 0;
		for(x=sx;x<p.GetSize();) {
			if(p.GetChess(x,y)==1) {
				dec = WritePattern(pt,p,x,y,dx,dy);
				for(int i=0;i<PATTERN_NUM;i++)if(Pattern(g_pattern[i],pt,false)){value-=DEFENCE*g_pattern_v[i];break;}
				y += dec*dy;
				x+dec*dx;
			}
			y+=dy,x+=dx;
		}
	}
	//左上搜索
	dx = 1,dy = -1;
	for(sy = 0;sy<p.GetSize();sy++) {
		x = 0;
		for(y=sy;y>=0;) {
			if(p.GetChess(x,y)==-1) {
				dec = WritePattern(pt,p,x,y,dx,dy);
				for(int i=0;i<PATTERN_NUM;i++)if(Pattern(g_pattern[i],pt,true)){value+=g_pattern_v[i];break;}
				y += dec*dy;
				x+dec*dx;
			}
			y+=dy,x+=dx;
		}
	}
	for(sx = 1;sx<p.GetSize();sx++) {
		y = p.GetSize()-1;
		for(x=sx;x<p.GetSize();) {
			if(p.GetChess(x,y)==-1) {
				dec = WritePattern(pt,p,x,y,dx,dy);
				for(int i=0;i<PATTERN_NUM;i++)if(Pattern(g_pattern[i],pt,true)){value+=g_pattern_v[i];break;}
				y += dec*dy;
				x+dec*dx;
			}
			y+=dy,x+=dx;
		}
	}
	for(sy = 0;sy<p.GetSize();sy++) {
		x = 0;
		for(y=sy;y>=0;) {
			if(p.GetChess(x,y)==1) {
				dec = WritePattern(pt,p,x,y,dx,dy);
				for(int i=0;i<PATTERN_NUM;i++)if(Pattern(g_pattern[i],pt,false)){value-=DEFENCE*g_pattern_v[i];break;}
				y += dec*dy;
				x+dec*dx;
			}
			y+=dy,x+=dx;
		}
	}
	for(sx = 1;sx<p.GetSize();sx++) {
		y = p.GetSize()-1;
		for(x=sx;x<p.GetSize();) {
			if(p.GetChess(x,y)==1) {
				dec = WritePattern(pt,p,x,y,dx,dy);
				for(int i=0;i<PATTERN_NUM;i++)if(Pattern(g_pattern[i],pt,false)){value-=DEFENCE*g_pattern_v[i];break;}
				y += dec*dy;
				x+dec*dx;
			}
			y+=dy,x+=dx;
		}
	}
	//StopCout("ValueOf");
	return value;
}

int GetValue(QiPan& q, int depth, bool max) {
	if(depth == 0) {
		return ValueOf(q);
	} else {
		int value = max?-INTMAX:INTMAX,temp;
		int pos = -1,all =q.GetSize()*q.GetSize() ;
		while((++pos)<all) {
			if(q.GetChess(pos%q.GetSize(), pos/q.GetSize())==0) {
				q.SetChess(pos%q.GetSize(), pos/q.GetSize(), max?1:-1);
				temp = GetValue(q, depth-1, !max);
				if(max && temp>=value) {
					value = temp;
				} else if(!max && temp<=value) {
					value = temp;
				}
				q.SetChess(pos%q.GetSize(), pos/q.GetSize(), 0);
			}
		}
		return value;
	}
}
int GetValueNega(QiPan& q, int depth, bool max) {
	if(depth==0) {
		return max?ValueOf(q):-ValueOf(q);
	} else {
		int value = -INTMAX,temp;
		int pos = -1,all = q.GetSize()*q.GetSize();
		while((++pos)<all) {
			if(q.GetChess(pos%q.GetSize(), pos/q.GetSize())==0 && q.GetNear(pos%q.GetSize(), pos/q.GetSize())>0) {
				q.SetChess(pos%q.GetSize(), pos/q.GetSize(), max?1:-1);
				temp = -GetValueNega(q,depth-1,!max);
				q.ClearChess(pos%q.GetSize(), pos/q.GetSize());
				if(temp>value)value = temp;
			}
		}
		return value;
	}
}

int times;
DWORD time;
int GetValueAlphaBeta(QiPan& q,int depth, int alpha,int beta,bool max) {
	if(depth == 0) {
		return ValueOf(q);
	} else {
		int temp;
		int pos = -1,all =q.GetSize()*q.GetSize() ;
		while((++pos)<all) {
			if(q.GetChess(pos%q.GetSize(), pos/q.GetSize())==0 && q.GetNear(pos%q.GetSize(), pos/q.GetSize())>0) {
				q.SetChess(pos%q.GetSize(), pos/q.GetSize(), max?1:-1);
				temp = GetValueAlphaBeta(q,depth-1, alpha,beta,  !max);
				q.ClearChess(pos%q.GetSize(), pos/q.GetSize());
				if(max) {
					if(alpha<temp)alpha = temp;
					if(alpha>beta)return alpha;
				} else {
					if(beta>temp)beta = temp;
					if(alpha>beta)return beta;
				}
			}
		}
		if(max)return alpha;
		else return beta;
	}
}

void fiveplay() {
	int len;
	int x,y;
	int max,mx,my,temp;
	cin>>len;
	QiPan* qp = new QiPan(len);
	while(1) {
		qp->Print();
		cout<<"你走（x,y）：";
		cin>>x>>y;
		if(qp->GetChess(x,y)==0) {
			qp->SetChess(x,y,1);
			vt = 0;
			max = -INTMAX,mx=-1,my=-1;
			for(int i=0;i<qp->GetSize()*qp->GetSize();i++) {
				if(qp->GetChess(i%qp->GetSize(),i/qp->GetSize()) == 0 && qp->GetNear(i%qp->GetSize(), i/qp->GetSize())) {
					qp->SetChess(i%qp->GetSize(), i/qp->GetSize(), -1);
					if(mx==-1)mx = i%qp->GetSize(),my=i%qp->GetSize();
					//temp = -GetValueNega(*qp, 2,false);
					temp = GetValueAlphaBeta(*qp, 2,max, INTMAX, false);
					if(temp>max) {
						max = temp;
						mx = i%qp->GetSize();
						my = i/qp->GetSize();
					}
					qp->ClearChess(i%qp->GetSize(), i/qp->GetSize());
				}
			}
			qp->SetChess(mx, my, -1);
			cout<<endl<<"计算了"<<vt<<"次棋盘评价";
		}
	}
}