#include "Point.h"



Point::Point(int x, int y)
{
	this->pos.x = x;
	this->pos.y = y;
}


Point::~Point()
{
}

void Point::connect(Point* next, Point* previous)
{
	this->next = next;
	this->previous = previous;
	previous->next = this;
	next->previous = this;
}
