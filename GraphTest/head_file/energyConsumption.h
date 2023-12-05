#pragma once
#include "randWS.h"
#include <string.h>

// TODO ��������
double RjTransfer(int n, int next){
	double x1 = LWS[n].getX(), y1 = LWS[n].getY(), x2 = LWS[next].getX(), y2 = LWS[next].getY();
	double d = dis(x1, y1, x2, y2);
	return d > d0 ? 0.00005*pow(d / 10, 4) + 100 : 0.05*pow(d/10, 2) + 100;
}

// �ж��Ƿ���
int TransDO(int n, double con){
	if (LWS[n].getRemainEnergy() > con){
		return 1;
	}
	else {
		return 0;
	}
}

// TODO ��������
double receiveEnergy(){
	return 100;
}
// �ɹ�
string succ(int n, double con){
	string s = " ��������:" + to_string(con) + " ʣ������:" + to_string(LWS[n].getRemainEnergy());
	return s;
}
// ʧ��
string defe(int n, double con){
	string s = "ʣ������:" + to_string(LWS[n].getRemainEnergy()) + " ������������:" + to_string(con) + " ����ʧ��!" + "\n";
	return s;
}


// LEACH �㷨, ��ͷnֱ�Ӵ������ݵ���վ
void LEACHtoTransfer(int n, int &needS){
	ofstream outfile;
	outfile.open(txt, ios::app);
	// �������&&��־�ַ���
	string s = "��ͷ" + to_string(n) + " ������������վ,";
	// TODO
	double consumption = LWS[n].getD() > d0 ? 0.00005*pow(LWS[n].getD() / 10.0, 4) + 100 : 0.05*pow(LWS[n].getD() / 10, 2) + 100;
	if (TransDO(n, consumption)){
		LWS[n].updateRemainEnergy(consumption);		// �ڵ㷢������
		s += succ(n, consumption) + " ����ɹ�!" + "\n";
		success++;
	}
	else{
		s += "��ͷ" + defe(n,consumption);
		needS = 1;
		defeat++;	// ����ʧ�ܴ���
	}
	cout << s;
	outfile << s;
	outfile.close();
}

// TODO EDM�㷨����/�������䵽��վ
void EDMtoTransfer(int n, int & needS){
	// ������ͷ�ڵ㣬�������վ���������
	int minR = n;
	double EAVGj = 0,	// EAVGj:��R(j)�е�ƽ��ʣ������
		numb = 0,	// numb��R(j)Ԫ�ظ������Ƚڵ�n�����վ������
		bt = 0.8;	// �ɵ��ڲ�������
	for (auto a : WSHeads){
		// ά������Ĵ�ͷ�ڵ���
		if (LWS[a].getD() < LWS[minR].getD()){
			minR = a;
		}
		// ����������ۼ�������numb
		if (LWS[a].getD() < LWS[n].getD()){
			EAVGj += LWS[a].getRemainEnergy();
			numb+=1;
		}
	}
	// ����ƽ������
	EAVGj = EAVGj / numb;
	// �м̽ڵ�ѡ������
	double newCj = 0;
	int ans = n;
	for (auto a : WSHeads){
		// ���������м�ѡ�����ӣ�ѡ����������ֵ��Ӧ�Ĵ�ͷ��Ϊ�м̽ڵ�
		if (LWS[a].getD() < LWS[n].getD()){
			double DISj = pow(dis(LWS[a].getX(), LWS[a].getY(), LWS[n].getX(), LWS[n].getY()), LWS[a].getD());
			double Cj = bt*LWS[minR].getD() / DISj + (1 - bt)*LWS[a].getRemainEnergy() / EAVGj;
			if (Cj > newCj){
				newCj = Cj;
				ans = a;
			}
		}
	}
	// ��û�к��ʵ���ֱ�Ӵ������ݵ���վ
	if (ans == n){
		LEACHtoTransfer(n, needS);
	}
	// �к��ʵ����ȴ����м̽ڵ�ans���ټ�����ansѡ�������ݵ���һ���ڵ�
	else{
		double consumption = RjTransfer(n, ans);
		string s = "��ͷ:" + to_string(n) + " �������ݵ���ͷ:" + to_string(ans);
		// cout << s;
		ofstream outfile;
		outfile.open(txt, ios::app);
		if (TransDO(n, consumption)){
			LWS[n].updateRemainEnergy(consumption);
			if (LWS[n].getRemainEnergy() < HeadMinEnergy){
				needS = 1;
				LWS[n].setCanBeHead(0);
			}
			s += succ(n, consumption) + "\n";
			outfile << s;
			outfile.close();
			cout << s;
			EDMtoTransfer(ans, needS);
		}
		else{
			defeat++;
			s += " ��ͷ" + defe(n, consumption);
			cout << s;
			outfile << s;
			outfile.close();
			needS = 1;
			return;
		}
	}
}

// ������������
void transData(){
	while (true)
	{
		if (Which == NUM){
			// �µ�һ�֣�ͳ��ǰr������
			double to = 0;
			for (int n = 0; n < NUM; n++){
				to += LWS[n].getRemainEnergy();
			}
			string s = "ǰ" + to_string(r) + "�ֹ㲥�ܴ���: " + to_string(showNum) + "\n";
			s += "ǰ" + to_string(r) + "�ִ�ͷѡ�ٴ���: " + to_string(seleNumber) + "\n";
			s += "ǰ" + to_string(r) + "������������: " + to_string(initEnergy*NUM - to) + "\n";
			s += "ǰ" + to_string(r) + "�����ݴ���ɹ������ܼ�: " + to_string(success) + "\n";
			s += "ǰ" + to_string(r) + "�����ݴ���ʧ�ܴ����ܼ�: " + to_string(defeat) + "\n";
			// �µ�һ��
			s += "########�� " + to_string(++r) + " ��########" + "\n";
			cout << s;
			// д�ļ�
			ofstream outfile;
			outfile.open(txt, ios::app);
			outfile << s;
			outfile.close();
		}
		Which %= NUM;
		int disNum = LWS[Which].getHeadNum();	// ���ڴصĴ�ͷ�ڵ�
		ofstream outfile;
		outfile.open(txt, ios::app);
		outfile << "******�ڵ�" << Which << "��������******" << endl;
		cout << "******�ڵ�" << Which << "��������******" << endl;
		if (LWS[Which].getIsAlone() || !LWS[Which].getSOrD() || LWS[Which].getRemainEnergy() <= WSMinENergy || LWS[Which].getHeadNum()==-1){
			outfile << "�ڵ�" << Which << "����������, �޷�����" << endl;
			cout << "�ڵ�" << Which << "����������, �޷�����" << endl;
			AloneTransfer++;	// �����ڵ㲻�ܴ������
			// �ж��Ƿ����
			if (checkEnd()){
				if (mode == 2) { Which++; }
				break;
			}
			Which++;
			continue;
		}
		
		// �ж��Ƿ��Ǵ�ͷ�ڵ�
		if (Which != disNum){
			string ss = "�ڵ�" + to_string(Which) + " ������������ͷ" + to_string(disNum);
			// ����Ǵ�ͷ�ڵ㣬ֱ�Ӹ����㷨ѡ��ͬ�Ĵ��䷽ʽ
			// ���Ǵ�ͷ�ڵ����ȴ�����ͷ����ͷ�ڸ����㷨ѡ���䷽ʽ
			double consumption = RjTransfer(Which, disNum);
			if (TransDO(Which, consumption)){
				LWS[Which].updateRemainEnergy(consumption);
				ss += succ(Which,consumption) + "\n";
				outfile << ss;
				cout << ss;
			}
			else{
				ss += " �ڵ�"+defe(Which,consumption);
				defeat++;
				outfile << ss;
				cout << ss;
				continue;
			}
		}
		outfile.close();
		int needS = 0;
		if (mode == 1){
			LEACHtoTransfer(disNum, needS);
		}
		else if(mode == 2){
			EDMtoTransfer(disNum, needS);
		}
		if (LWS[disNum].getRemainEnergy() < HeadMinEnergy || needS){
			ofstream outfile;
			outfile.open(txt, ios::app);
			outfile << "���ڴ�ͷ����С�ڴ�ͷ�����ֵ " << HeadMinEnergy << " ������ѡ�ٴ�ͷ" << endl;
			outfile.close();
			cout << "���ڴ�ͷ����С�ڴ�ͷ�����ֵ " << HeadMinEnergy << " ������ѡ�ٴ�ͷ" << endl;
			Which++;
			seleNumber++;	// ����ѡ�ٴ�ͷ
			WSHeads.clear();	// LEACH�㷨��Ҫ����ѡ�ٴ�ͷ
			break;
		}
		Which++;
	}
}