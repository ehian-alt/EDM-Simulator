#include "head_file\operation.h"
#include "head_file\initGraph.h"

int main(){	
	setCoor();	// 生成随机坐标
	ssc();	// 选择算法->选簇头->入簇
	init_Graph();	// 初始化画板
	while (1)
	{
		cleardevice();	// 刷新
		Lines();	// 连线
		drawSrandWs();	// 用随机生成的坐标 绘制无线传感器
		if (Timer(200, 0))
		{
			FlushBatchDraw();	// 刷新每一帧
		}
		choseOp();
	}	
	
	EndBatchDraw();			// 关闭双缓存
	closegraph();
	return 0;
}