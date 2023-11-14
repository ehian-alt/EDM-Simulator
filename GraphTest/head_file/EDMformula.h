// EDM��ʽ
#pragma once
#include <iostream>
#include "Statics.h"

double a1 = 0.3, a2 = 0.4, a3 = 0.3;

// ��������, Di: 
double Dfactor(double Di){
	return (Dmax - Di) / (Dmax - Dmin);
}

// ʣ����������
double Efactor(double Ei, double E0){
	double Eavg = (Ei + E0) / 2.00;		// TODO
	return (Ei - Eavg) / E0;	// TODO
}

// �ܶ�����
double Nfactor(float n){
	return n / (1.00 / p - 1);
}

// �Ľ���ֵ��ʽ
double TofEDM(double Efac, double Dfac, double Nfac){
	return (p * (a1*Efac + a2 * Dfac + a3 * Nfac)) / (1 - (p * fmod(r, 1 / p)));
}

// ���Ŵ�ͷ��Ŀ
int Kopt(){
	return 10;
}