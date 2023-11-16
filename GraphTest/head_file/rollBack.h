#include "randWS.h"
// 重置初始状态
void rollBack(){
	isEnd = 0;
	mode = 0;
	r = 1;
	Which = 0;
	WSHeads.clear();
	cluster.clear();
	alone.clear();
	for (int i = 0; i < NUM; i++){
		LWS[i].setCanBeHead(1);
		LWS[i].setIsHead(0);
		LWS[i].setRemainEnergy(10000);	// TODO
		LWS[i].setHeadNum(-1);
	}
}
