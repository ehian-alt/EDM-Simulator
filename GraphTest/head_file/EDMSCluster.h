// EDM 选举簇头， 节点入簇
using namespace std;
#include <map>
#include "randWS.h"
#include "EDMformula.h"
#include <algorithm>

double u1 = 0.9, u2 = 0.012, u3 = 0.088;

// 排序方式
bool cmp(pair<int, double> a, pair<int, double> b){
	return a.second > b.second;
}

map<int, double> tmp;

// 打印簇信息
void printCluster(){
	// 打印簇头节点
	cout << endl << "簇头节点WSHeads：";
	for (auto a : WSHeads){
		cout << a << "  ";
	}
	//
	for (auto a : cluster){
		cout << endl << "簇：";
		for (auto b : a){
			cout << b << " ";
		}
	}
	//
	cout << endl << "孤立 节点：" << alone.size() << "  :";
	for (auto a : alone){
		cout << a << " ";
	}
	cout << endl << endl;
}

// 计算阈值
void cTn(){
	for (int i = 0; i < NUM; i++) {
		double Dfac = Dfactor(LWS[i].getD());	// 距离因子
		double Efac = Efactor(LWS[i].getRemainEnergy(), LWS[i].getInitEnergy());	// 能量因子
		double Nfac = Nfactor(i);	// TODO	密度因子
		double T = TofEDM(Efac, Dfac, Nfac);	// 阈值
		LWS[i].setTofEDM(T);
		// 重置每个节点的簇头节点和是否为簇头节点属性
		LWS[i].setHeadNum(-1);
		LWS[i].setIsHead(0);
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

	// 选举阈值最高的Kopt个节点作为簇头
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

// 入簇偏好度计算
double cluEi(int n, int a){
	double t1 = u1 * (LWS[a].getRemainEnergy() - Eavg) / LWS[n].getRemainEnergy();
	double t2 = u2 * (R - dis(LWS[n].getX(), LWS[n].getY(), LWS[a].getX(), LWS[a].getY()) / 10) / R;	// R TODO
	//cout << "能量……………………" << t1 << endl << "距离……………………" << t2 << endl;
	/*
	double t3 = u3 * (9 - LWS[a].getNeighborN()) / 9;	// 9 TODO
	return t1 + t2 + t3;
	*/
	
	return t1 + t2;
}

// 根据入簇偏好度入簇
int EDMclu(int n, vector<vector<int>> &clusterEDM){
	int ans = -1;
	double tmp = -1000;
	for (auto a : WSHeads){
		if (dis(LWS[n].getX(), LWS[n].getY(), LWS[a].getX(), LWS[a].getY()) < R && 
			clusterEDM[a].size() < (NUM - deadWS.size()) / WSHeads.size() + 3 && 
			cluEi(n, a) > tmp && LWS[n].getSOrD()){
			ans = a;
			tmp = cluEi(n, a);
			LWS[n].setHeadNum(a);
		}
	}

	if (ans == -1){
		LWS[n].setIsAlone(1);
		cout << "节点" << n << "孤立" << endl;
		return 0;
	}
	else{
		cout << "节点" << n << "加入" << ans << "所在簇" << endl;
		clusterEDM[ans].push_back(n);
	}
	return 0;
}


// EDM算法入簇
void EDMsCluster(){
	vector<vector<int>> clusterEDM(100);
	for (int i = 0; i < NUM; i++){
		clusterEDM[i] = {};
	}
	cluster.clear();
	for (auto a : WSHeads)
	{
		cluster.push_back({ a });
	}
	// 遍历节点选择入簇
	for (int n = 0; n < NUM; n++){
		// 筛出非簇头节点
		auto it = find(WSHeads.begin(), WSHeads.end(), n);
		// 若不是簇头节点则根据偏好度入簇
		if (!LWS[n].getIsAlone() && it == WSHeads.end()){
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
	// 打印簇信息
	printCluster();
}
