#include <easyx.h>

void init_Graph(){
	initgraph(1100, 700);	// 初始化
	BeginBatchDraw();		// 开启双缓存，图像不闪烁
	setbkcolor(RGB(255, 252, 236));	// 设置画布背景
	cleardevice();
}