#include <stdio.h>	// ��׼��������
#include <LEACHSCluster.h>
#include "energyConsumption.h"
#include "rollBack.h"

// run this
void runThis(){
	transData();
	if (!isEnd){
		SelectHead(mode);
		if (mode == 2 && !isEnd){
			EDMsCluster();
		}
	}
}

// ѡ���㷨
void choseMode(){
	while (mode != 1 && mode != 2){
		cout << "LEACH(1)  LEACH-EDM(2): ";
		cin >> mode;
	}
}

// ѡ���㷨->ѡ��ͷ->���
void ssc(){
	choseMode();
	txt = mode == 1 ? "LEACH.txt" : "LEACH-EDM.txt";
	ofstream outfile;
	outfile.open(txt, ios::out);
	outfile << "��ʼ���ڵ����: " << NUM << endl << "�ڵ��ʼ������: " << initEnergy << endl << "���ι㲥��Ҫ����: " << showConsume << endl;
	outfile << "########�� 1 ��########" << endl;
	outfile.close();
	if (mode == 1){
		HeadMinEnergy = 5000.0;
		firstSelectHead();
		sCluster();
	}
	else{
		HeadMinEnergy = 3000.0;
		SelectHead(mode);
		EDMsCluster();
	}
	// mode == 1 ? sCluster(): EDMsCluster();
}

// ѡ�����
void choseOperation(){
	
	cout << "\t1������ִ��" << endl << "\t2������������" << endl << "\t3�����ó�ʼ״̬" << endl << "\t4��ˢ��" << endl << "��ѡ�������ţ�";
	cin >> op;
	if (op == 1 || op == 2){
		runThis();
	}
	else if (op == 3){
		// ���ó�ʼ״̬
		rollBack();
	}
}

// �жϲ���
void choseOp(){
	if (op == 3){
		ssc();
		op = 0;
	}
	else if (op == 4){
		op = 0;
	}
	else if (isEnd || op != 2){
		choseOperation();
	}
	else {
		runThis();
	}
}

