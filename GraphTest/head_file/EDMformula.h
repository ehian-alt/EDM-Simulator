// EDM��ʽ
#pragma once
#include <iostream>
#include "Statics.h"

double a1 = 0.8, a2 = 0.1, a3 = 0.1;	// ���������룬�ܶ�

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
	//cout << "��������######################" << a2 * (Dmax - Di) / (Dmax - Dmin) << endl;
	return (Dmax - Di) / (Dmax - Dmin);
}

// ʣ����������
double Efactor(double Ei, double E0){
	//cout << "��������&&&&&&&&&&&&&&&&&&" << (Ei - Eavg) / E0 << endl;
	// return (Ei - Eavg) / E0;	// TODO
	return (Ei - HeadMinEnergy) / E0;	// TODO
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
	//cout << "�ܶ�����$$$$$$$$$$$$$$$$$$" << a3 * thisN / (1.00 / p - 1) << endl;
	return thisN / (1.00 / p - 1);
}

// �Ľ���ֵ��ʽ
double TofEDM(double Efac, double Dfac, double Nfac){
	// TODO return (p * (a1 * Efac + a2 * Dfac + a3 * Nfac)) / (1 - (p * fmod(r, 1 / p)));
	return a1 * Efac + a2 * Dfac - a3 * Nfac;
}

// ���Ŵ�ͷ��Ŀ
void Kopt(){
	// TODO
	kop = (NUM - deadWS.size()) / 10 + 2;
}