// 传统LEACH算法公式
#pragma once
#include <cmath>
#include "Statics.h"
using namespace std;

float Tn(){
	return (float)(p / (1 - (p * (fmod(r, 1/p)))));
};
