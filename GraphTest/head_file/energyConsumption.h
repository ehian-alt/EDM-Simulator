#pragma once
#include "randWS.h"

// TODO ��������
double sendEnergy(int x, int y, int desx, int desy){
	double x1 = x / 10, y1 = y / 10, x2 = desx / 10, y2 = desy / 10;
	double d = dis(x1, y1, x2, y2);
	return 0.00005*pow(d, 4) + 100;
}

// TODO ��������
double receiveEnergy(){
	return 100;
}

// TODO EDM�㷨����/�������䵽��վ
void EDMtoTransfer(int n){

}

// LEACH �㷨��ͷ�������ݵ���վ
void LEACHtoTransfer(int n){
	// TODO
	double consumption = 0.00005*pow(LWS[n].getD(), 4) + 100;
	LWS[n].updateRemainEnergy(consumption);
	cout << "��ͷ" << n << "�������ݵ���վ������������"<< consumption << "ʣ������" << LWS[n].getRemainEnergy() << endl;
}

// ������������
void transData(){
	while (true)
	{
		Which %= 100;
		int disNum = LWS[Which].getHeadNum();	// ���ڴصĴ�ͷ�ڵ�
		// �ж��Ƿ��Ǵ�ͷ�ڵ�
		if (LWS[Which].getIsAlone() || LWS[Which].getSOrD() == 0 || LWS[Which].getRemainEnergy() < 0){
			// cout << "�����ڵ�: " << Which  << " �޷���������" << endl;
			if (deadWS.size() + alone.size() >= NUM){
				isEnd = 1;
				cout << "�������ڵ���ڵ�ȫ�� ����/������ֵ ��ִ�н���" << endl;
				break;
			}
			Which++;
			continue;
		}
		if (Which != disNum){
			cout << "�ڵ�" << Which << "����ͷ" << disNum << endl;
			// ����Ǵ�ͷ�ڵ㣬ֱ�Ӹ����㷨ѡ��ͬ�Ĵ��䷽ʽ
			// ���Ǵ�ͷ�ڵ����ȴ�����ͷ����ͷ�ڸ����㷨ѡ���䷽ʽ
			double consumption = sendEnergy(LWS[Which].getX(), LWS[Which].getY(), LWS[disNum].getX(), LWS[disNum].getY());
			LWS[Which].updateRemainEnergy(consumption);	// �ڵ㷢������
			LWS[disNum].updateRemainEnergy(receiveEnergy());	// ��ͷ������������
			cout << endl << "�ڵ� " << Which << " �������ݵ���ͷ " << disNum << "��������: " << consumption << " ʣ������: " << LWS[Which].getRemainEnergy() << endl
				<< "��ͷ�ڵ� " << disNum << " ʣ������: " << LWS[disNum].getRemainEnergy() << endl;
			if (LWS[Which].getRemainEnergy() < HeadMinEnergy)
			{
				LWS[Which].setCanBeHead(0);
				deadWS.insert(Which);
			}
		}
		if (mode == 1){
			LEACHtoTransfer(disNum);
			if (LWS[disNum].getRemainEnergy() < HeadMinEnergy){
				cout << "��ͷ����С����ֵ " << HeadMinEnergy << "��������ѡ�ٴ�ͷ" << endl;

				LWS[disNum].setCanBeHead(0);	// С����ֵ����������Ϊ��ͷ
				Which++;	
				r++;	// ��Ҫ����ѡ��ͷ������+1
				WSHeads.clear();	// LEACH�㷨��Ҫ����ѡ�ٴ�ͷ
				break;
			}
		}
		else if(mode == 2){
			EDMtoTransfer(disNum);
		}
		Which++;
	}
}