// WS类
#include <easyx.h>
#include <math.h>
#include <iostream>
#include "Statics.h"

// 无线传感器类
class WS{
	private:
		int X;	// x坐标
		int Y;	// y坐标
		int isHead = 0;	// 是否为簇头节点
		int SOrD = 1;	// 1为存活，0为死亡
		double initEnergy;	// 初始能量
		double remainEnergy;	// 剩余能量
		int number;	// 编号
		double D;	// 与基站的距离
		double s;	// 随机生成一个0~1之间的随机小数
		double TofEDM;	// EDM算法阈值存储
		int canBeHead = 1;	// 剩余能量是否具备成为簇头的条件 （1表示能够成为簇头）
		int HeadNum = -1;	// 所在簇的簇头节点编号
		int isAlone = 0;	// 是否为孤立节点, 1表示是孤立节点，0表示不是孤立节点
		int neighborN;		// 邻居节点个数

	public:
		WS(){}
		WS(int x, int y, int i, double initE);

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
		void setRemainEnergy(int energy);
		void updateRemainEnergy(double consumption);

		void setTofEDM(double T);
		double getTofEDM();

		void setCanBeHead(int b);
		int getCanBeHead();

		void setHeadNum(int n);
		int getHeadNum();

		int getSOrD();
		void setSOrD(int b);

		int getIsAlone();
		void setIsAlone(int b);

		int getNeighborN();
		void setNeighborN(int n);
};

// WS构造函数
WS::WS(int x, int y, int i, double initE){
	X = x;
	Y = y;
	double x1 = x, y1 = y;
	D = dis(x1, y1, 0, 0);
	number = i;
	initEnergy = initE;	// TODO	初始能量
	remainEnergy = initE;	// TODO 剩余能量
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

void WS::setIsHead(int b){	// 是否为簇头节点
	isHead = b;
}

int WS::getIsHead(){	// 是否为簇头节点
	return isHead;
}

double WS::getD(){		// 与基站的距离
	return D;
}

void WS::setS(double _s){	// 随机生成一个0~1之间的随机小数
	s = _s;
}

double WS::getInitEnergy(){		// 初始能量
	return initEnergy;
}

double WS::getRemainEnergy(){	// 初始能量
	return remainEnergy;
}

void WS::setRemainEnergy(int energy){	// 剩余能量
	remainEnergy = energy;
}

void WS::updateRemainEnergy(double consumption){	// 更新剩余能量（减去参数能量）
	remainEnergy -= consumption;
}

void WS::setTofEDM(double T){	// EDM算法阈值存储
	TofEDM = T;
}

double WS::getTofEDM(){		// EDM算法阈值存储
	return TofEDM;
}

void WS::setCanBeHead(int b){	// 剩余能量是否具备成为簇头的条件 （1表示能够成为簇头）
	canBeHead = b;
}

int WS::getCanBeHead(){		// 剩余能量是否具备成为簇头的条件 （1表示能够成为簇头）
	return canBeHead;
}

int WS::getHeadNum(){	// 所在簇的簇头节点编号
	return HeadNum;
}

void WS::setHeadNum(int n){		// 所在簇的簇头节点编号
	HeadNum = n;
}

int WS::getSOrD(){
	return SOrD;
}

void WS::setSOrD(int b){
	SOrD = b;
}

int WS::getIsAlone(){
	return isAlone;
}

void WS::setIsAlone(int b){
	isAlone = b;
}

void WS::setNeighborN(int n){
	neighborN = n;
}

int WS::getNeighborN(){
	return neighborN;
}