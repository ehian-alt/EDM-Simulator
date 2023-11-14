// EDM ѡ�ٴ�ͷ�� �ڵ����
using namespace std;
#include <map>
#include "randWS.h"
#include "EDMformula.h"
#include <algorithm>

// ����ʽ
bool cmp(pair<int, double> a, pair<int, double> b){
	return a.second > a.second;
}

map<int, double> tmp;

void cTn(){
	for (int i = 0; i < NUM; i++){
		double Dfac = Dfactor(LWS[i].getD());	// ��������
		double Efac = Efactor(LWS[i].getRemainEnergy(), LWS[i].getInitEnergy());	// ��������
		double Nfac = Nfactor( 10.00 );	// TODO	�ܶ�����
		double T = TofEDM(Efac, Dfac, Nfac);	// ��ֵ
		LWS[i].setTofEDM(T);
		tmp[i] = LWS[i].getTofEDM();
	}
}

// EDM�Ľ��㷨��ͷѡ��
void selectByEDM(){
	cTn();
	vector<pair<int, double>> EDMTsort(tmp.begin(), tmp.end());	// ���ڵ㰴EDM�㷨��ֵ����keyΪ��ţ�valueΪ��ֵ
	sort(EDMTsort.begin(), EDMTsort.end(), cmp);	// ��ֵ����

	// dayin
	for (unsigned int i = 0; i < EDMTsort.size(); i++){
		cout << EDMTsort[i].first + 1 << " " << EDMTsort[i].second << endl;
	}

	// ѡ����ֵ��ߵ�Kopt���ڵ���Ϊ��ͷ
	for (int i = 0; i < Kopt(); i++){
		int k = EDMTsort[i].first;
		LWS[k].setIsHead(1);
		WSHeads.push_back(k);
	}
}
// EDM�㷨���
void EDMsCluster(){

}
