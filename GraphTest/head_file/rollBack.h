#include "randWS.h"
// 重置初始状态
void rollBack(){
	isEnd = 0;	// 是否结束
	mode = 0;	// 何种算法
	r = 1;		// 轮数
	Which = 0;
	WSHeads.clear();
	cluster.clear();
	alone.clear();
	deadWS.clear();
	for (int i = 0; i < NUM; i++){
		LWS[i].setIsAlone(0);
		LWS[i].setSOrD(1);
		LWS[i].setCanBeHead(1);
		LWS[i].setIsHead(0);
		LWS[i].setRemainEnergy(10000);	// TODO
		LWS[i].setHeadNum(-1);
	}
}
