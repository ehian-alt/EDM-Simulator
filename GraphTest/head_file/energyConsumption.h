#pragma once
#include "randWS.h"

// TODO 发送能量
double sendEnergy(int x, int y, int desx, int desy){
	double x1 = x / 10, y1 = y / 10, x2 = desx / 10, y2 = desy / 10;
	double d = dis(x1, y1, x2, y2);
	return 0.00005*pow(d, 4) + 100;
}

// TODO 接收能量
double receiveEnergy(){
	return 100;
}

// LEACH 算法簇头传输数据到基站
void LEACHtoTransfer(int n){
	// TODO
	double consumption = 0.00005*pow(LWS[n].getD() / 10.0, 4) + 100;
	LWS[n].updateRemainEnergy(consumption);
	cout << "簇头" << n << "传输数据到基站，消耗能量：" << consumption << "剩余能量" << LWS[n].getRemainEnergy() << endl;
}

// TODO EDM算法单跳/多跳传输到基站
void EDMtoTransfer(int n){
	// 遍历簇头节点，若距离基站更近则计算
	int minR = n;
	double EAVGj = 0, numb = 0, bt = 0.8;
	for (auto a : WSHeads){
		if (LWS[a].getD() < LWS[minR].getD()){
			minR = a;
		}
		if (LWS[a].getD() < LWS[n].getD()){
			EAVGj += LWS[a].getRemainEnergy();
			numb+=1;
		}
	}
	EAVGj = EAVGj / numb;
	double newCj = 0;
	int ans = n;
	for (auto a : WSHeads){
		if (LWS[a].getD() < LWS[n].getD()){
			double DISj = pow(dis(LWS[a].getX(), LWS[a].getY(), LWS[n].getX(), LWS[n].getY()), LWS[a].getD());
			double Cj = bt*LWS[minR].getD() / DISj + (1 - bt)*LWS[a].getRemainEnergy() / EAVGj;
			if (Cj > newCj){
				newCj = Cj;
				ans = a;
			}
		}
	}
	if (ans == n){
		LEACHtoTransfer(n);
	}
	else{
		double consumption = 0.00005*pow(dis(LWS[ans].getX(), LWS[ans].getY(), LWS[n].getX(), LWS[n].getY()) / 10.0, 4) + 100;
		LWS[n].updateRemainEnergy(consumption);
		cout << "簇头" << n << "传输数据簇头" << ans << " ，消耗能量：" << consumption << "剩余能量" << LWS[n].getRemainEnergy() << endl;
		EDMtoTransfer(ans);
	}
}

// 遍历发送能量
void transData(){
	while (true)
	{
		Which %= 100;
		int disNum = LWS[Which].getHeadNum();	// 所在簇的簇头节点
		// 判断是否是簇头节点
		if (LWS[Which].getIsAlone() || LWS[Which].getSOrD() == 0 || LWS[Which].getRemainEnergy() < 0){
			// cout << "孤立节点: " << Which  << " 无法传输数据" << endl;
			if (deadWS.size() + alone.size() >= NUM){
				isEnd = 1;
				cout << "除孤立节点外节点全部 死亡/低于阈值 ，执行结束" << endl;
				break;
			}
			Which++;
			continue;
		}
		if (Which != disNum){
			cout << "节点" << Which << "传簇头" << disNum << endl;
			// 如果是簇头节点，直接根据算法选择不同的传输方式
			// 不是簇头节点则先传到簇头，簇头在根据算法选择传输方式
			double consumption = sendEnergy(LWS[Which].getX(), LWS[Which].getY(), LWS[disNum].getX(), LWS[disNum].getY());
			LWS[Which].updateRemainEnergy(consumption);	// 节点发送能量
			LWS[disNum].updateRemainEnergy(receiveEnergy());	// 簇头接收消耗能量
			cout << endl << "节点 " << Which << " 传输数据到簇头 " << disNum << "消耗能量: " << consumption << " 剩余能量: " << LWS[Which].getRemainEnergy() << endl
				<< "簇头节点 " << disNum << " 剩余能量: " << LWS[disNum].getRemainEnergy() << endl;
			if (LWS[Which].getRemainEnergy() < HeadMinEnergy)
			{
				LWS[Which].setCanBeHead(0);
				deadWS.insert(Which);
			}
		}
		if (mode == 1){
			LEACHtoTransfer(disNum);
			if (LWS[disNum].getRemainEnergy() < HeadMinEnergy){
				cout << "簇头能量小于阈值 " << HeadMinEnergy << "，需重新选举簇头" << endl;
				LWS[disNum].setCanBeHead(0);	// 小于阈值，不能再作为簇头
				Which++;	
				r++;	// 需要重新选簇头，轮数+1
				WSHeads.clear();	// LEACH算法需要重新选举簇头
				break;
			}
		}
		else if(mode == 2){
			cout << "EDM算法数据传输" << endl;
			EDMtoTransfer(disNum);
			/*
			*/
			if (LWS[disNum].getRemainEnergy() < HeadMinEnergy){
				cout << "簇头能量小于阈值 " << HeadMinEnergy << "，需重新选举簇头" << endl;
				LWS[disNum].setCanBeHead(0);	// 小于阈值，不能再作为簇头
				Which++;
				r++;	// 需要重新选簇头，轮数+1
				WSHeads.clear();	// LEACH算法需要重新选举簇头
				break;
			}
		}
		Which++;
	}
}