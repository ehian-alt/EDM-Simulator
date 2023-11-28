// EDM��ʽ
#pragma once
#include <iostream>
#include "Statics.h"

double a1 = 0.1, a2 = 0.3, a3 = 0.6;

void gEavg(){
	double totle = 0;
	for (int i = 0; i < NUM; i++)
	{
		totle += LWS[i].getRemainEnergy() > 0 ? LWS[i].getRemainEnergy() : 0;
	}
	Eavg = totle / (NUM - deadWS.size());
}

// ��������, Di: 
double Dfactor(double Di){
	return (Dmax - Di) / (Dmax - Dmin) / 10;
}

// ʣ����������
double Efactor(double Ei, double E0){
	return (Ei - Eavg) / E0;	// TODO
}

// �ܶ�����
double Nfactor(int n){
	// 1�������ھӽڵ㼯��
	int thisN = 0;
	for (int i = 0; i < NUM; i++){
		thisN += dis(LWS[i].getX(), LWS[i].getY(), LWS[n].getX(), LWS[n].getY()) < R ? 1 : 0;
	}
	LWS[n].setNeighborN(thisN);
	// 2, ���㲢�����ܶ�����
	return thisN / (1.00 / p - 1);
}

// �Ľ���ֵ��ʽ
double TofEDM(double Efac, double Dfac, double Nfac){
	return (p * (a1 * Efac + a2 * Dfac + a3 * Nfac)) / (1 - (p * fmod(r, 1 / p)));
}

// ���Ŵ�ͷ��Ŀ
void Kopt(){
	// TODO
	kop = 12;
}