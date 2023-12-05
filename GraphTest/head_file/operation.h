#include <stdio.h>	// 标准输入输入
#include <LEACHSCluster.h>
#include "energyConsumption.h"
#include "rollBack.h"

// run this
void runThis(){
	transData();
	if (!isEnd){
		SelectHead(mode);
		if (mode == 2 && !isEnd){
			EDMsCluster();
		}
	}
}

// 选择算法
void choseMode(){
	while (mode != 1 && mode != 2){
		cout << "LEACH(1)  LEACH-EDM(2): ";
		cin >> mode;
	}
}

// 选择算法->选簇头->入簇
void ssc(){
	choseMode();
	txt = mode == 1 ? "LEACH.txt" : "LEACH-EDM.txt";
	ofstream outfile;
	outfile.open(txt, ios::out);
	outfile << "初始化节点个数: " << NUM << endl << "节点初始化能量: " << initEnergy << endl << "单次广播需要能量: " << showConsume << endl;
	outfile << "########第 1 轮########" << endl;
	outfile.close();
	if (mode == 1){
		HeadMinEnergy = 5000.0;
		firstSelectHead();
		sCluster();
	}
	else{
		HeadMinEnergy = 3000.0;
		SelectHead(mode);
		EDMsCluster();
	}
	// mode == 1 ? sCluster(): EDMsCluster();
}

// 选择操作
void choseOperation(){
	
	cout << "\t1：继续执行" << endl << "\t2：运行至结束" << endl << "\t3：重置初始状态" << endl << "\t4：刷新" << endl << "请选择操作序号：";
	cin >> op;
	if (op == 1 || op == 2){
		runThis();
	}
	else if (op == 3){
		// 重置初始状态
		rollBack();
	}
}

// 判断操作
void choseOp(){
	if (op == 3){
		ssc();
		op = 0;
	}
	else if (op == 4){
		op = 0;
	}
	else if (isEnd || op != 2){
		choseOperation();
	}
	else {
		runThis();
	}
}

