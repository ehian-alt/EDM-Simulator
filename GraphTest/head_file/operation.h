#include <stdio.h>	// ��׼��������
#include <LEACHSCluster.h>
#include "energyConsumption.h"
#include "rollBack.h"

// run this
void runThis(){
	cout << "########�� " << r << " ��########" << endl;
	transData();
	SelectHead(mode);
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
	SelectHead(mode);
	if (mode == 1)	sCluster();
	else EDMsCluster();
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

