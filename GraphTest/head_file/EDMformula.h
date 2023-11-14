// EDM公式
#pragma once
#include <iostream>
#include "Statics.h"

double a1 = 0.3, a2 = 0.4, a3 = 0.3;

// 距离因子, Di: 
double Dfactor(double Di){
	return (Dmax - Di) / (Dmax - Dmin);
}

// 剩余能量因子
double Efactor(double Ei, double E0){
	double Eavg = (Ei + E0) / 2.00;		// TODO
	return (Ei - Eavg) / E0;	// TODO
}

// 密度因子
double Nfactor(float n){
	return n / (1.00 / p - 1);
}

// 改进阈值公式
double TofEDM(double Efac, double Dfac, double Nfac){
	return (p * (a1*Efac + a2 * Dfac + a3 * Nfac)) / (1 - (p * fmod(r, 1 / p)));
}

// 最优簇头数目
int Kopt(){
	return 10;
}