﻿// 常量
#pragma once
#include <vector>

using namespace std;

#define dis( a, b, c, d ) pow(( c - a ) * ( c - a ) + ( d - b ) * ( d - b ), 0.5 )

#define REDIUS 10

#define N 99999	// 生成的随机小数精度

static vector<vector<int>> cluster;	// 每个簇内节点（编号）集合

static vector<int> alone; // 孤立节点

static vector<int> WSHeads; // 簇头节点编号容器

static const int NUM = 100;	// 初始化WS的个数

static const double p = 0.05;	// 常量p

static double Dmax = 0, Dmin = 2000;	// 节点离基站最大、最小距离

static int r = 1;	// 轮数

static float R = 200; // TODO 节点最大可通信范围

static int mode;	// 1：LEACH算法		2：LEACH-EDM算法

static unsigned int op = 0;	// 选择操作

static unsigned int Which = 0;	// 到哪一个WS传输数据了？（0~99）

static const double HeadMinEnergy = 3000.0;	// 节点作为簇头需要的最小能量



