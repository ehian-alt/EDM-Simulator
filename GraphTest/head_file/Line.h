#include <easyx.h>
#include <stdio.h>
#include <stdlib.h>

void drawLine(int x, int y, int des_x, int des_y){
	line(x, y, des_x, des_y);
}

void drawNum(int x, int y, int num){
	char s[25];
	sprintf_s(s, "%2d", num);
	outtextxy(x - 8, y - 8, s);
}