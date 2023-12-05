// �������WS
#pragma once
#include "WS.h"
#include "BS.h"
#include "Line.h"

static vector<WS> LWS(NUM);	// WS����

static vector<vector<int>> coorList;	// WS��������

// �ж��Ƿ��ص����ص�����0�����ص�����1
int isFlow(int x, int y){
	int n = coorList.size();
	for (int i = 0; i < n; i++){
		if ( dis(x, y, coorList[i][0], coorList[i][1] ) <= 21 || ( x <= 60 && y <= 60 )){
			return 0;
		}
	}
	cout << "��" << n << "��WS��" << x << ", " << y << endl;
	return 1;
}

// �������NUM��WS
void setCoor(){
	srand((unsigned)time(0));	// ���õ�ǰʱ��Ϊ����
	int i = 0;
	while (i < NUM){
		int x = rand() % 1100;
		int y = rand() % 700;
		// �ж��ص�
		if (isFlow(x, y)){
			LWS[i] = WS( x, y, i, initEnergy);
			
			Dmin = min( LWS[i].getD(), Dmin );
			Dmax = max( LWS[i].getD(), Dmax );
			// �����ص��������coorList����
			vector<int> A;
			A.push_back(x);
			A.push_back(y);
			coorList.push_back(A);
			A.clear();
			i++;
		}
	}
}

void drawSrandWs(){
	// ����BS
	d_bs(0, 0);
	for (int i = 0; i < NUM; i++){
		// ����WS
		LWS[i].d_ws();
		drawNum(LWS[i].getX(), LWS[i].getY(), i);
	}
}

void Lines(){
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	for (unsigned int i = 0; i < cluster.size(); i++){
		for (unsigned int j = 1; j < cluster[i].size(); j++){
			drawLine(LWS[cluster[i][j]].getX(), LWS[cluster[i][j]].getY(), LWS[cluster[i][0]].getX(), LWS[cluster[i][0]].getY());
		}
	}
}

int checkEnd(){
	double to = 0;
	for (int n = 0; n < NUM; n++){
		to += LWS[n].getRemainEnergy();
	}
	if (alone.size() >= NUM * 0.85 || deadWS.size() >= NUM*0.85 || 100 * to / (initEnergy*NUM) < 15){
		isEnd = 1;
		cout << "ʣ������ռ��:" << 100 * to / (initEnergy*NUM) << "%" << endl;
		string s = mode == 1 ? "LEACH" : "LEACH-EDM";
		s += "\n����ʣ��ڵ���ռ�ȵ���85%/����ʣ�������ȵ���15%,ģ��ִ�н���\n";
		s += "�ܹ�����: " + to_string(r) + "\n";
		s += "�����ڵ㴫������ܼ�: " + to_string(AloneTransfer) + "\n";
		s += "����ʣ������: " + to_string(to) + "\n";
		s += "���ڵ�㲥������Ϣ����: " + to_string(showNum * showConsume) + "\n";
		s += "�㲥�ܴ���: " + to_string(showNum) + "\n";
		s += "��ͷѡ�ٴ���: " + to_string(seleNumber) + "\n";
		s += "����������: " + to_string(initEnergy*NUM - to) + "\n";
		s += "���ݴ���ɹ������ܼ�: " + to_string(success) + "\n";
		s += "���ݴ���ʧ�ܴ����ܼ�: " + to_string(defeat);
		cout << s << endl;
		// д���ļ�
		ofstream outfile;
		outfile.open(txt, ios::app);
		outfile << s;
		outfile.close();
		return 1;
	}
	return 0;
}
