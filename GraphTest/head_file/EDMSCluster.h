// EDM ѡ�ٴ�ͷ�� �ڵ����
using namespace std;
#include <map>
#include "randWS.h"
#include "EDMformula.h"
#include <algorithm>

double u1 = 0.01, u2 = 0.90, u3 = 0.08;	// ����������

// ����ʽ
bool cmp(pair<int, double> a, pair<int, double> b){
	return a.second > b.second;
}

map<int, double> tmp;

// ��ӡ����Ϣ
void printCluster(){
	// ��ӡ��ͷ�ڵ�
	cout << endl << "��ͷ�ڵ�WSHeads��";
	for (auto a : WSHeads){
		cout << a << "  ";
	}
	//
	int nn = 0;
	for (auto a : cluster){
		cout << endl << "��(" << a.size() << "): ";
		nn += a.size();
		for (auto b : a){
			cout << b << " ";
		}
	}
	cout << endl << "���ڹ�: " << nn << endl;
	// �����ڵ�
	ofstream outfile;
	outfile.open(txt, ios::app);
	outfile << "�����ڵ����:" << alone.size() << endl;
	outfile.close();

	cout << "���� �ڵ�(" << alone.size() << "): ";
	for (auto a : alone){
		cout << a << " ";
	}
	cout << endl << endl;
}

// ������ֵ
void cTn(){
	for (int i = 0; i < NUM; i++) {
		double Dfac = Dfactor(LWS[i].getD());	// ��������
		double Efac = Efactor(LWS[i].getRemainEnergy(), LWS[i].getInitEnergy());	// ��������
		double Nfac = Nfactor(i);	// TODO	�ܶ�����
		double T = TofEDM(Efac, Dfac, Nfac);	// ��ֵ
		LWS[i].setTofEDM(T);
		// ����ÿ���ڵ�Ĵ�ͷ�ڵ���Ƿ�Ϊ��ͷ�ڵ�����
		LWS[i].setHeadNum(-1);
		LWS[i].setIsHead(0);
		tmp[i] = T;
	}
}

// new������ֵ
void newcTn(){
	for (int i = 0; i < NUM; i++) {
		double T = LWS[i].getRemainEnergy() >= HeadMinEnergy ? rand() % (N + 1) / (float)(N + 1) : 0;
		double Dfac = Dfactor(LWS[i].getD())*0.7;	// ��������
		double Efac = Efactor(LWS[i].getRemainEnergy(), LWS[i].getInitEnergy())*0.3;	// ��������
		cout << "��������: " << Dfac << endl << "��������: " << Efac << endl << "�����T: " << T << endl << "�����Tֵ: " << T + Dfac + Efac << endl;
		LWS[i].setTofEDM(T + Dfac + Efac);
		// ����ÿ���ڵ�Ĵ�ͷ�ڵ���Ƿ�Ϊ��ͷ�ڵ�����
		LWS[i].setHeadNum(-1);
		LWS[i].setIsHead(0);
		tmp[i] = T;
	}
}


// EDM�Ľ��㷨��ͷѡ��
void selectByEDM(){
	Kopt();
	WSHeads.clear();
	gEavg();
	// cTn();
	newcTn();
	vector<pair<int, double>> EDMTsort(tmp.begin(), tmp.end());	// ���ڵ㰴EDM�㷨��ֵ����keyΪ��ţ�valueΪ��ֵ
	sort(EDMTsort.begin(), EDMTsort.end(), cmp);	// ��ֵ����

	// ѡ����ֵ��ߵ�Kopt���ڵ���Ϊ��ͷ
	unsigned int i = 0;
	while (kop > 0 && i < NUM && i < EDMTsort.size())
	{
		int k = EDMTsort[i].first;
		if (LWS[k].getRemainEnergy() > HeadMinEnergy && LWS[k].getCanBeHead()){
			WSHeads.push_back(k);
			LWS[k].setHeadNum(k);
			LWS[k].setIsHead(1);
			LWS[k].setIsAlone(0);
			kop--;
		}
		i++;
	}
}

// ���ƫ�öȼ���
double cluEi(int n, int a){
	double t1 = u1 * (LWS[a].getRemainEnergy() - HeadMinEnergy) / HeadMinEnergy;		// ��ƽ��������Ϊ��ͷ��ֵ����֤Ϊ������������ΪHeadMinEnergy
	double t2 = u2 * (R - dis(LWS[n].getX(), LWS[n].getY(), LWS[a].getX(), LWS[a].getY())) / R;	// R TODO
	// cout << "��������������������" << t1 << endl << "���롭��������������" << t2 << endl;
	/*
	double t3 = u3 * (9 - LWS[a].getNeighborN()) / 9;	// 9 TODO
	return t1 + t2 + t3;
	*/
	
	return t1 + t2;
}

// �������ƫ�ö����
int EDMclu(int n, vector<vector<int>> &clusterEDM){
	int ans = -1;
	double tmp = -1000;
	for (auto a : WSHeads){
		if (dis(LWS[n].getX(), LWS[n].getY(), LWS[a].getX(), LWS[a].getY()) < R && 
			clusterEDM[a].size() < (NUM - deadWS.size()) / WSHeads.size() + 2 && 
			cluEi(n, a) > tmp && LWS[n].getSOrD()){
			ans = a;
			tmp = cluEi(n, a);
			LWS[n].setHeadNum(a);
		}
	}
	
	if (ans == -1){
		alone.insert(n);	// ��ʱ����
		LWS[n].setIsAlone(1);
		//cout << "�ڵ�" << n << "����" << endl;
		return 0;
	}
	else{
		//cout << "�ڵ�" << n << "����" << ans << "���ڴ�" << endl;
		clusterEDM[ans].push_back(n);
	}
	return 0;
}


// EDM�㷨���
void EDMsCluster(){
	vector<vector<int>> clusterEDM(100);
	for (int i = 0; i < NUM; i++){
		clusterEDM[i] = {};
	}
	cluster.clear();
	for (auto a : WSHeads){
		cluster.push_back({ a });
	}
	// �����ڵ�ѡ�����
	for (int n = 0; n < NUM; n++){
		// ɸ���Ǵ�ͷ�ڵ�
		auto it = find(WSHeads.begin(), WSHeads.end(), n);
		// �����Ǵ�ͷ�ڵ������ƫ�ö����
		if (LWS[n].getSOrD() && it == WSHeads.end()){
			EDMclu(n, clusterEDM);
		}
	}
	int i = 0;
	for (auto a : WSHeads){
		for (auto b : clusterEDM[a]){
			cluster[i].push_back(b);
		}
		i++;
	}
	// ��ӡ����Ϣ
	printCluster();
}
