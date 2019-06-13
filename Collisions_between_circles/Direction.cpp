#include "Direction.h"



Direction::Direction()
{
	x = 0;
	y = 0;
	speed = 0;
}

Direction::Direction(int x_, int y_, int speed_) {
	x = x_;
	y = y_;
	speed = speed_;
}


Direction::~Direction()
{
}


