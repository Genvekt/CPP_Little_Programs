#pragma once
#include "Direction.h"

class Circle
{
public:
	Circle();
	Circle(int x, int y, int radius);
	~Circle();
	int x;        
	int y;        
	int radius;
	int color;
	Direction vector;
	bool isCollide(Circle* c1);
	void Collide(Circle* circle);
	void move(int w, int h);
};

