#include "randWS.h"
// 重置初始状态
void rollBack(){
	isEnd = 0;	// 是否结束
	mode = 0;	// 何种算法
	r = 1;		// 轮数
	success = 0;	// 成功次数
	defeat = 0;	// 失败次数
	AloneTransfer = 0; // 孤立/死亡无法传输
	Which = 0;
	WSHeads.clear();	// 簇头节点编号容器
	cluster.clear();	// 簇信息
	alone.clear();	// 孤立节点容器
	deadWS.clear();	// 死亡节点容器
	numOfDeadWS = 0; // 死亡节点个数
	for (int i = 0; i < NUM; i++){
		LWS[i].setIsAlone(0);
		LWS[i].setSOrD(1);
		LWS[i].setCanBeHead(1);
		LWS[i].setIsHead(0);
		LWS[i].setRemainEnergy(10000);	// TODO
		LWS[i].setHeadNum(-1);
	}
}
