#include <time.h>
// ��ʱ������������
int Timer(int duration, int id){
	static int startTime[10];
	int endTime = clock();
	if (endTime - startTime[id] > duration){
		startTime[id] = endTime;
		return 1;
	}
	return 0;
}