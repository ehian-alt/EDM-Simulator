#include <easyx.h>

#define r 20

struct Data_ball
{
	int x;
	int y;
	int radiu;
};

void draw_ball(Data_ball dball){
	setfillcolor(LIGHTRED);
	solidcircle(dball.x, dball.y, dball.radiu);
}

void move_ball(Data_ball dball, int dx, int dy){
	dball.x += dx;
	dball.y += dy;
}
