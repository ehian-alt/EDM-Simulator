#include <easyx.h>

// 绘制基站
void d_bs(int x, int y){
	IMAGE img[2];
	loadimage(img + 0, _T("./IMGS/jz2.png"), 50, 50);
	loadimage(img + 1, _T("./IMGS/jz1.png"), 50, 50);
	putimage(x, y, img + 0, SRCAND);
	putimage(x, y, img + 1, SRCPAINT);
}