#include <easyx.h>

void init_Graph(){
	initgraph(1100, 700);	// ��ʼ��
	BeginBatchDraw();		// ����˫���棬ͼ����˸
	setbkcolor(RGB(255, 252, 236));	// ���û�������
	cleardevice();
}