// WS类
#include <easyx.h>
#include <math.h>
#include <iostream>
#include "LEACHformula.h"

// 无线传感器类
class WS{
	private:
		int X;	// x坐标
		int Y;	// y坐标
		int isHead = 0;	// 是否为簇头节点
		double initEnergy;	// 初始能量
		double remainEnergy;	// 剩余能量
		int number;	// 编号
		double D;	// 与基站的距离
		double s;	// 随机生成一个0~1之间的随机小数
		double TofEDM;	// EDM算法阈值存储
		int canBeHead = 1;	// 剩余能量是否具备成为簇头的条件
		int HeadNum = -1;	// 所在簇的簇头节点编号

	public:
		WS(){}
		WS(int x, int y, int i);

		void d_ws();
		double getD();

		int getX();
		int getY();

		void setIsHead(int b);
		int getIsHead();

		void setS(double _s);
		double getS();
		
		double getInitEnergy();

		double getRemainEnergy();
		double setRemainEnergy();
		void updateRemainEnergy(double consumption);

		void setTofEDM(double T);
		double getTofEDM();

		void setCanBeHead(int b);
		int getCanBeHead();

		void setHeadNum(int n);
		int getHeadNum();
};

// WS构造函数
WS::WS(int x, int y, int i){
	X = x;
	Y = y;
	double x1 = x / 10, y1 = y / 10;
	D = dis(x1, y1, 0.1, 0.1);
	number = i;
	initEnergy = 10000;	// TODO	初始能量
	remainEnergy = 10000;	// TODO 剩余能量
}

void WS::d_ws(){
	if (isHead){
		setfillcolor(RED);
		solidcircle(X, Y, REDIUS);
	}
	else
	{
		setfillcolor(WHITE);
		setlinecolor(BLACK);
		fillcircle(X, Y, REDIUS);
	}
}

int WS::getX(){
	return X;
}

int WS::getY(){
	return Y;
}

double WS::getS(){
	return s;
}

void WS::setIsHead(int b){
	isHead = b;
}

int WS::getIsHead(){
	return isHead;
}

double WS::getD(){
	return D;
}

void WS::setS(double _s){
	s = _s;
}

double WS::getInitEnergy(){
	return initEnergy;
}

double WS::getRemainEnergy(){
	return remainEnergy;
}

void WS::updateRemainEnergy(double consumption){
	remainEnergy -= consumption;
}

void WS::setTofEDM(double T){
	TofEDM = T;
}

double WS::getTofEDM(){
	return TofEDM;
}

void WS::setCanBeHead(int b){
	canBeHead = b;
}

int WS::getCanBeHead(){
	return canBeHead;
}

int WS::getHeadNum(){
	return HeadNum;
}

void WS::setHeadNum(int n){
	HeadNum = n;
}