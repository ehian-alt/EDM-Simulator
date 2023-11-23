// EDM ѡ�ٴ�ͷ�� �ڵ����
using namespace std;
#include <map>
#include "randWS.h"
#include "EDMformula.h"
#include <algorithm>

double u1 = 0.2, u2 = 0.4, u3 = 0.4;

// ����ʽ
bool cmp(pair<int, double> a, pair<int, double> b){
	return a.second > a.second;
}

map<int, double> tmp;

// ������ֵ
void cTn(){
	for (int i = 0; i < NUM; i++) {
		double Dfac = Dfactor(LWS[i].getD());	// ��������
		double Efac = Efactor(LWS[i].getRemainEnergy(), LWS[i].getInitEnergy());	// ��������
		double Nfac = Nfactor(i);	// TODO	�ܶ�����
		double T = TofEDM(Efac, Dfac, Nfac);	// ��ֵ
		LWS[i].setTofEDM(T);
		tmp[i] = T;
	}
}

// EDM�Ľ��㷨��ͷѡ��
void selectByEDM(){
	Kopt();
	WSHeads.clear();
	gEavg();
	cTn();
	vector<pair<int, double>> EDMTsort(tmp.begin(), tmp.end());	// ���ڵ㰴EDM�㷨��ֵ����keyΪ��ţ�valueΪ��ֵ
	sort(EDMTsort.begin(), EDMTsort.end(), cmp);	// ��ֵ����
	// dayin
	for (unsigned int i = 0; i < EDMTsort.size(); i++){
		cout << EDMTsort[i].first + 1 << " " << EDMTsort[i].second << endl;
	}

	// ѡ����ֵ��ߵ�Kopt���ڵ���Ϊ��ͷ
	int i = 0;
	while (i < kop && i < NUM)
	{
		int k = EDMTsort[i].first;
		if (LWS[k].getRemainEnergy() > HeadMinEnergy && LWS[k].getCanBeHead()){
			WSHeads.push_back(k);
			LWS[k].setHeadNum(k);
			LWS[k].setIsHead(1);
			LWS[k].setIsAlone(0);
			i++;
		}
	}
}

// ���ƫ�öȼ���
double cluEi(int n, int a){
	double t1 = u1 * (LWS[a].getRemainEnergy() - Eavg) / LWS[n].getRemainEnergy();
	double t2 = u2 * (R - dis(LWS[n].getX(), LWS[n].getY(), LWS[a].getX(), LWS[a].getY())) / R;	// R TODO
	double t3 = u3 * (9 - LWS[a].getNeighborN()) / 9;	// TODO
	return t1 + t2 + t3;
}

// �������ƫ�ö����
int EDMclu(int n){
	int ans = -1;
	double tmp = -1000;
	for (auto a : WSHeads){
		if (cluEi(n, a) > tmp && dis(LWS[n].getX(), LWS[n].getY(), LWS[a].getX(), LWS[a].getY()) < 500 && clusterEDM[a].size() < 10){
			ans = a;
			tmp = cluEi(n, a);
			LWS[n].setHeadNum(a);
		}
	}

	if (ans == -1){
		alone.push_back(n);
		LWS[n].setIsAlone(1);
		cout << "�ڵ�" << n << "����" << endl;
		return 0;
	}
	else{
		clusterEDM[ans].push_back(n);
	}
	return 0;
}


// EDM�㷨���
void EDMsCluster(){
	clusterEDM.clear();
	cluster.clear();
	for (auto a : WSHeads)
	{
		clusterEDM[a].push_back(a);
		cluster.push_back({ a });
		cout << a << endl;
	}
	// �����ڵ�ѡ�����
	for (int n = 0; n < NUM; n++){
		// ɸ���Ǵ�ͷ�ڵ�
		auto it = find(WSHeads.begin(), WSHeads.end(), n);
		// �����Ǵ�ͷ�ڵ������ƫ�ö����
		if (it == WSHeads.end()){
			EDMclu(n);
		}
	}
	int i = 0;
	for (auto a : WSHeads){
		for (auto b : clusterEDM[a]){
			cluster[i].push_back(b);
		}
		i++;
	}
}
