#pragma once
#include "randWS.h"
#include <string.h>

// TODO 发送能量
double RjTransfer(int n, int next){
	double x1 = LWS[n].getX(), y1 = LWS[n].getY(), x2 = LWS[next].getX(), y2 = LWS[next].getY();
	double d = dis(x1, y1, x2, y2);
	return d > d0 ? 0.00005*pow(d / 10, 4) + 100 : 0.05*pow(d/10, 2) + 100;
}

// 判断是否发送
int TransDO(int n, double con){
	if (LWS[n].getRemainEnergy() > con){
		return 1;
	}
	else {
		return 0;
	}
}

// TODO 接收能量
double receiveEnergy(){
	return 100;
}
// 成功
string succ(int n, double con){
	string s = " 消耗能量:" + to_string(con) + " 剩余能量:" + to_string(LWS[n].getRemainEnergy());
	return s;
}
// 失败
string defe(int n, double con){
	string s = "剩余能量:" + to_string(LWS[n].getRemainEnergy()) + " 低于所需能量:" + to_string(con) + " 传输失败!" + "\n";
	return s;
}


// LEACH 算法, 簇头n直接传输数据到基站
void LEACHtoTransfer(int n, int &needS){
	ofstream outfile;
	outfile.open(txt, ios::app);
	// 构造输出&&日志字符串
	string s = "簇头" + to_string(n) + " 传输数据至基站,";
	// TODO
	double consumption = LWS[n].getD() > d0 ? 0.00005*pow(LWS[n].getD() / 10.0, 4) + 100 : 0.05*pow(LWS[n].getD() / 10, 2) + 100;
	if (TransDO(n, consumption)){
		LWS[n].updateRemainEnergy(consumption);		// 节点发送能量
		s += succ(n, consumption) + " 传输成功!" + "\n";
		success++;
	}
	else{
		s += "簇头" + defe(n,consumption);
		needS = 1;
		defeat++;	// 传输失败次数
	}
	cout << s;
	outfile << s;
	outfile.close();
}

// TODO EDM算法单跳/多跳传输到基站
void EDMtoTransfer(int n, int & needS){
	// 遍历簇头节点，若距离基站更近则计算
	int minR = n;
	double EAVGj = 0,	// EAVGj:在R(j)中的平均剩余能量
		numb = 0,	// numb：R(j)元素个数（比节点n距离基站更近）
		bt = 0.8;	// 可调节参数：β
	for (auto a : WSHeads){
		// 维护最近的簇头节点编号
		if (LWS[a].getD() < LWS[minR].getD()){
			minR = a;
		}
		// 距离更近则累加能量和numb
		if (LWS[a].getD() < LWS[n].getD()){
			EAVGj += LWS[a].getRemainEnergy();
			numb+=1;
		}
	}
	// 计算平均能量
	EAVGj = EAVGj / numb;
	// 中继节点选择因子
	double newCj = 0;
	int ans = n;
	for (auto a : WSHeads){
		// 遍历计算中继选择因子，选择最大的因子值对应的簇头作为中继节点
		if (LWS[a].getD() < LWS[n].getD()){
			double DISj = pow(dis(LWS[a].getX(), LWS[a].getY(), LWS[n].getX(), LWS[n].getY()), LWS[a].getD());
			double Cj = bt*LWS[minR].getD() / DISj + (1 - bt)*LWS[a].getRemainEnergy() / EAVGj;
			if (Cj > newCj){
				newCj = Cj;
				ans = a;
			}
		}
	}
	// 若没有合适的则直接传输数据到基站
	if (ans == n){
		LEACHtoTransfer(n, needS);
	}
	// 有合适的则，先传给中继节点ans，再继续由ans选择发送数据到下一个节点
	else{
		double consumption = RjTransfer(n, ans);
		string s = "簇头:" + to_string(n) + " 传输数据到簇头:" + to_string(ans);
		// cout << s;
		ofstream outfile;
		outfile.open(txt, ios::app);
		if (TransDO(n, consumption)){
			LWS[n].updateRemainEnergy(consumption);
			if (LWS[n].getRemainEnergy() < HeadMinEnergy){
				needS = 1;
				LWS[n].setCanBeHead(0);
			}
			s += succ(n, consumption) + "\n";
			outfile << s;
			outfile.close();
			cout << s;
			EDMtoTransfer(ans, needS);
		}
		else{
			defeat++;
			s += " 簇头" + defe(n, consumption);
			cout << s;
			outfile << s;
			outfile.close();
			needS = 1;
			return;
		}
	}
}

// 遍历发送能量
void transData(){
	while (true)
	{
		if (Which == NUM){
			// 新的一轮，统计前r轮数据
			double to = 0;
			for (int n = 0; n < NUM; n++){
				to += LWS[n].getRemainEnergy();
			}
			string s = "前" + to_string(r) + "轮广播总次数: " + to_string(showNum) + "\n";
			s += "前" + to_string(r) + "轮簇头选举次数: " + to_string(seleNumber) + "\n";
			s += "前" + to_string(r) + "轮消耗总能量: " + to_string(initEnergy*NUM - to) + "\n";
			s += "前" + to_string(r) + "轮数据传输成功次数总计: " + to_string(success) + "\n";
			s += "前" + to_string(r) + "轮数据传输失败次数总计: " + to_string(defeat) + "\n";
			// 新的一轮
			s += "########第 " + to_string(++r) + " 轮########" + "\n";
			cout << s;
			// 写文件
			ofstream outfile;
			outfile.open(txt, ios::app);
			outfile << s;
			outfile.close();
		}
		Which %= NUM;
		int disNum = LWS[Which].getHeadNum();	// 所在簇的簇头节点
		ofstream outfile;
		outfile.open(txt, ios::app);
		outfile << "******节点" << Which << "传输数据******" << endl;
		cout << "******节点" << Which << "传输数据******" << endl;
		if (LWS[Which].getIsAlone() || !LWS[Which].getSOrD() || LWS[Which].getRemainEnergy() <= WSMinENergy || LWS[Which].getHeadNum()==-1){
			outfile << "节点" << Which << "孤立或死亡, 无法传输" << endl;
			cout << "节点" << Which << "孤立或死亡, 无法传输" << endl;
			AloneTransfer++;	// 孤立节点不能传输次数
			// 判断是否结束
			if (checkEnd()){
				if (mode == 2) { Which++; }
				break;
			}
			Which++;
			continue;
		}
		
		// 判断是否是簇头节点
		if (Which != disNum){
			string ss = "节点" + to_string(Which) + " 传输数据至簇头" + to_string(disNum);
			// 如果是簇头节点，直接根据算法选择不同的传输方式
			// 不是簇头节点则先传到簇头，簇头在根据算法选择传输方式
			double consumption = RjTransfer(Which, disNum);
			if (TransDO(Which, consumption)){
				LWS[Which].updateRemainEnergy(consumption);
				ss += succ(Which,consumption) + "\n";
				outfile << ss;
				cout << ss;
			}
			else{
				ss += " 节点"+defe(Which,consumption);
				defeat++;
				outfile << ss;
				cout << ss;
				continue;
			}
		}
		outfile.close();
		int needS = 0;
		if (mode == 1){
			LEACHtoTransfer(disNum, needS);
		}
		else if(mode == 2){
			EDMtoTransfer(disNum, needS);
		}
		if (LWS[disNum].getRemainEnergy() < HeadMinEnergy || needS){
			ofstream outfile;
			outfile.open(txt, ios::app);
			outfile << "存在簇头能量小于簇头最低阈值 " << HeadMinEnergy << " 需重新选举簇头" << endl;
			outfile.close();
			cout << "存在簇头能量小于簇头最低阈值 " << HeadMinEnergy << " 需重新选举簇头" << endl;
			Which++;
			seleNumber++;	// 重新选举簇头
			WSHeads.clear();	// LEACH算法需要重新选举簇头
			break;
		}
		Which++;
	}
}