// LEACH 簇头选举 WS节点入簇
#include <iostream>
#include <stdio.h>
#include <vector>
#include "EDMSCluster.h"

// 选距离最近的簇头入簇
int cDist(int x, int y, int n){
	float mdis = 3000;
	int ans = -1;
	// 找出最近距离的簇头
	for (auto a : WSHeads){
		float tmp = (float)dis(x, y, LWS[a].getX(), LWS[a].getY());
		if (tmp < mdis && tmp <= R){
			ans = a;
			mdis = tmp;
		}
	}
	if (ans == -1){
		alone.push_back(n);
		cout << "节点" << n << "孤立" << endl;
		return 0;
	}
	
	for (unsigned int i = 0; i < cluster.size(); i++){
		if (cluster[i][0] == ans){
			cluster[i].push_back(n);
			LWS[n].setHeadNum(ans);
			cout << "节点" << n+1 << "加入簇头" << ans+1 << "所在簇" << endl;
			return 1;
		}
	}
	return 1;
}

// LEACH算法节点入簇
void sCluster(){
	for (auto a : WSHeads){
		cluster.push_back({ a });
	}

	// 遍历节点选择入簇
	for (int n = 0; n < NUM; n++){
		// 筛出非簇头节点
		auto it = find(WSHeads.begin(), WSHeads.end(), n);
		// 若不是簇头节点则选择离自己最近的簇头入簇
		if (it == WSHeads.end()){
			cDist(LWS[n].getX(), LWS[n].getY(), n);
		}
	}

	for (auto a : cluster){
		cout << endl << "簇：";
		for (auto b : a){
			cout << b+1 << " ";
		}
	}
	cout << endl << "孤立节点:";
	for (auto a : alone){
		cout << a+1 << " ";
	}
	cout << endl;
}

// LEACH算法选举簇头
void selectByLEACH(){
	for (int i = 0; i < NUM; i++){
		// LEACH算法选举簇头：
		LWS[i].setS(rand() % (N + 1) / (float)(N + 1));
		// cout << s << " " << Tn() << endl;
		if (LWS[i].getS() < Tn()){
			LWS[i].setIsHead(1);
			LWS[i].setHeadNum(i);
			WSHeads.push_back(i);
		}
	}
}

void SelectHead(int mode){
	if (mode == 1){
		selectByLEACH();
	}
	else if (mode == 2){
		//  LEACH-EDM算法选举簇头
		selectByEDM();
	}

	cout << endl << "簇头节点";
	for (auto a : WSHeads){
		cout << a+1 << "  ";
	}
	cout << endl << endl;
}