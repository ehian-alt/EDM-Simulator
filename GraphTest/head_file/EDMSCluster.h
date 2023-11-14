// EDM 选举簇头， 节点入簇
using namespace std;
#include <map>
#include "randWS.h"
#include "EDMformula.h"
#include <algorithm>

// 排序方式
bool cmp(pair<int, double> a, pair<int, double> b){
	return a.second > a.second;
}

map<int, double> tmp;

void cTn(){
	for (int i = 0; i < NUM; i++){
		double Dfac = Dfactor(LWS[i].getD());	// 距离因子
		double Efac = Efactor(LWS[i].getRemainEnergy(), LWS[i].getInitEnergy());	// 能量因子
		double Nfac = Nfactor( 10.00 );	// TODO	密度因子
		double T = TofEDM(Efac, Dfac, Nfac);	// 阈值
		LWS[i].setTofEDM(T);
		tmp[i] = LWS[i].getTofEDM();
	}
}

// EDM改进算法簇头选举
void selectByEDM(){
	cTn();
	vector<pair<int, double>> EDMTsort(tmp.begin(), tmp.end());	// 各节点按EDM算法阈值排序，key为编号，value为阈值
	sort(EDMTsort.begin(), EDMTsort.end(), cmp);	// 按值排序

	// dayin
	for (unsigned int i = 0; i < EDMTsort.size(); i++){
		cout << EDMTsort[i].first + 1 << " " << EDMTsort[i].second << endl;
	}

	// 选举阈值最高的Kopt个节点作为簇头
	for (int i = 0; i < Kopt(); i++){
		int k = EDMTsort[i].first;
		LWS[k].setIsHead(1);
		WSHeads.push_back(k);
	}
}
// EDM算法入簇
void EDMsCluster(){

}
