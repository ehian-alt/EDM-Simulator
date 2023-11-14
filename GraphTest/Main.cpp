#include <stdio.h>	// 标准输入输入
#include <easyx.h>	// 绘图库
#include <myTimer.h>	//  定时器
#include <LEACHSCluster.h>
#include "head_file\initGraph.h"
#include "head_file\energyConsumption.h"

int main(){	
	cout << "LEACH(1)  LEACH-EDM(2): ";
	cin >> mode;
	init_Graph();	// 初始化

	setCoor();	// 随机坐标
	SelectHead(mode);
	sCluster();
	while (1)
	{
		cleardevice();	// 刷新
		drawSrandWs();	// 用随机生成的坐标 绘制无线传感器
		if (Timer(200, 0))
		{
			FlushBatchDraw();	// 刷新每一帧
		}
		cin >> op;
		transData();
	}	
	
	EndBatchDraw();			// 关闭双缓存
	closegraph();
	return 0;
}