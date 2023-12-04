// 随机生成WS
#pragma once
#include "WS.h"
#include "BS.h"
#include "Line.h"

static vector<WS> LWS(NUM);	// WS容器

static vector<vector<int>> coorList;	// WS坐标容器

// 判断是否重叠，重叠返回0，不重叠返回1
int isFlow(int x, int y){
	int n = coorList.size();
	for (int i = 0; i < n; i++){
		if ( dis(x, y, coorList[i][0], coorList[i][1] ) <= 21 || ( x <= 60 && y <= 60 )){
			return 0;
		}
	}
	cout << "第" << n << "个WS：" << x << ", " << y << endl;
	return 1;
}

// 随机生成NUM个WS
void setCoor(){
	srand((unsigned)time(0));	// 设置当前时间为种子
	int i = 0;
	while (i < NUM){
		int x = rand() % 1100;
		int y = rand() % 700;
		// 判断重叠
		if (isFlow(x, y)){
			LWS[i] = WS( x, y, i, initEnergy);
			
			Dmin = min( LWS[i].getD(), Dmin );
			Dmax = max( LWS[i].getD(), Dmax );
			// 将不重叠坐标加入coorList容器
			vector<int> A;
			A.push_back(x);
			A.push_back(y);
			coorList.push_back(A);
			A.clear();
			i++;
		}
	}
}

void drawSrandWs(){
	// 绘制BS
	d_bs(0, 0);
	for (int i = 0; i < NUM; i++){
		// 绘制WS
		LWS[i].d_ws();
		drawNum(LWS[i].getX(), LWS[i].getY(), i);
	}
}

void Lines(){
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	for (unsigned int i = 0; i < cluster.size(); i++){
		for (unsigned int j = 1; j < cluster[i].size(); j++){
			drawLine(LWS[cluster[i][j]].getX(), LWS[cluster[i][j]].getY(), LWS[cluster[i][0]].getX(), LWS[cluster[i][0]].getY());
		}
	}
}
