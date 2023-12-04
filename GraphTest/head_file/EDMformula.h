// EDM公式
#pragma once
#include <iostream>
#include "Statics.h"

double a1 = 0.8, a2 = 0.1, a3 = 0.1;	// 能量，距离，密度

void gEavg(){
	double totle = 0;
	for (int i = 0; i < NUM; i++)
	{
		totle += LWS[i].getRemainEnergy() > 0 ? LWS[i].getRemainEnergy() : 0;
	}
	Eavg = totle / (NUM - deadWS.size());
}

// 距离因子, Di: 
double Dfactor(double Di){
	//cout << "距离因子######################" << a2 * (Dmax - Di) / (Dmax - Dmin) << endl;
	return (Dmax - Di) / (Dmax - Dmin);
}

// 剩余能量因子
double Efactor(double Ei, double E0){
	//cout << "能量因子&&&&&&&&&&&&&&&&&&" << (Ei - Eavg) / E0 << endl;
	// return (Ei - Eavg) / E0;	// TODO
	return (Ei - HeadMinEnergy) / E0;	// TODO
}

// 密度因子
double Nfactor(int n){
	// 1，计算邻居节点集合
	int thisN = 0;
	for (int i = 0; i < NUM; i++){
		thisN += dis(LWS[i].getX(), LWS[i].getY(), LWS[n].getX(), LWS[n].getY()) < R ? 1 : 0;
	}
	LWS[n].setNeighborN(thisN);
	// 2, 计算并返回密度因子
	//cout << "密度因子$$$$$$$$$$$$$$$$$$" << a3 * thisN / (1.00 / p - 1) << endl;
	return thisN / (1.00 / p - 1);
}

// 改进阈值公式
double TofEDM(double Efac, double Dfac, double Nfac){
	// TODO return (p * (a1 * Efac + a2 * Dfac + a3 * Nfac)) / (1 - (p * fmod(r, 1 / p)));
	return a1 * Efac + a2 * Dfac - a3 * Nfac;
}

// 最优簇头数目
void Kopt(){
	// TODO
	kop = (NUM - deadWS.size()) / 10 + 2;
}