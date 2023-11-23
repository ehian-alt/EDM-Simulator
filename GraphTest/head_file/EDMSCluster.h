// EDM 选举簇头， 节点入簇
using namespace std;
#include <map>
#include "randWS.h"
#include "EDMformula.h"
#include <algorithm>

double u1 = 0.2, u2 = 0.4, u3 = 0.4;

// 排序方式
bool cmp(pair<int, double> a, pair<int, double> b){
	return a.second > a.second;
}

map<int, double> tmp;

// 计算阈值
void cTn(){
	for (int i = 0; i < NUM; i++) {
		double Dfac = Dfactor(LWS[i].getD());	// 距离因子
		double Efac = Efactor(LWS[i].getRemainEnergy(), LWS[i].getInitEnergy());	// 能量因子
		double Nfac = Nfactor(i);	// TODO	密度因子
		double T = TofEDM(Efac, Dfac, Nfac);	// 阈值
		LWS[i].setTofEDM(T);
		tmp[i] = T;
	}
}

// EDM改进算法簇头选举
void selectByEDM(){
	Kopt();
	WSHeads.clear();
	gEavg();
	cTn();
	vector<pair<int, double>> EDMTsort(tmp.begin(), tmp.end());	// 各节点按EDM算法阈值排序，key为编号，value为阈值
	sort(EDMTsort.begin(), EDMTsort.end(), cmp);	// 按值排序
	// dayin
	for (unsigned int i = 0; i < EDMTsort.size(); i++){
		cout << EDMTsort[i].first + 1 << " " << EDMTsort[i].second << endl;
	}

	// 选举阈值最高的Kopt个节点作为簇头
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

// 入簇偏好度计算
double cluEi(int n, int a){
	double t1 = u1 * (LWS[a].getRemainEnergy() - Eavg) / LWS[n].getRemainEnergy();
	double t2 = u2 * (R - dis(LWS[n].getX(), LWS[n].getY(), LWS[a].getX(), LWS[a].getY())) / R;	// R TODO
	double t3 = u3 * (9 - LWS[a].getNeighborN()) / 9;	// TODO
	return t1 + t2 + t3;
}

// 根据入簇偏好度入簇
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
		cout << "节点" << n << "孤立" << endl;
		return 0;
	}
	else{
		clusterEDM[ans].push_back(n);
	}
	return 0;
}


// EDM算法入簇
void EDMsCluster(){
	clusterEDM.clear();
	cluster.clear();
	for (auto a : WSHeads)
	{
		clusterEDM[a].push_back(a);
		cluster.push_back({ a });
		cout << a << endl;
	}
	// 遍历节点选择入簇
	for (int n = 0; n < NUM; n++){
		// 筛出非簇头节点
		auto it = find(WSHeads.begin(), WSHeads.end(), n);
		// 若不是簇头节点则根据偏好度入簇
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
