#include "Circle.h"
#include <math.h> 
using namespace std;



Circle::Circle()
{
	x = 0;
	y = 0; 
	radius = 0;
	color = 0;
}

Circle::Circle(int x, int y, int radius)
{
	this->x = x;
	this->y = y;
	this->radius = radius;
	color = 0;
}


Circle::~Circle()
{

}
bool Circle::isCollide(Circle* c)
{
	float distance = sqrt(pow(c->x - this->x, 2) + pow(c->y - this->y, 2));
	float next_distance = sqrt(pow((c->x+c->vector.x*0.01) - (this->x+this->vector.x * 0.01), 2) + pow((c->y + c->vector.y * 0.01) - (this->y + this->vector.y * 0.01), 2));
	if (c->radius + this->radius >= distance && next_distance< distance) {
		return true;
	}
	return false;
}

void Circle::Collide(Circle* circle)
{
	float R1 = this->radius;
	float x1 = this->vector.x;
	float y1 = this->vector.y;
	
	float R2 = circle->radius;
	float x2 = circle->vector.x;
	float y2 = circle->vector.y;

	float xb = (R1 * R1 * (2 * x1 - x2) + R2 * R2 * x2) / (R1 * R1 + R2 * R2);
	float yb = (R1 * R1 * (2 * y1 - y2) + R2 * R2 * y2) / (R1 * R1 + R2 * R2);

	float xa = (R1 * R1 * (2 * x1 - x2) + R2 * R2 * x2) / (R1 * R1 + R2 * R2) + x2 - x1;
	float ya = (R1 * R1 * (2 * y1 - y2) + R2 * R2 * y2) / (R1 * R1 + R2 * R2) + y2 - y1;

	this->vector.x = xa;
	this->vector.y = ya;
	this->vector.speed = sqrt(xa * xa + ya * ya);

	circle->vector.x = xb;
	circle->vector.y = yb;
	circle->vector.speed = sqrt(xb * xb + yb * yb);

}

void Circle::move(int w, int h)
{
	x += vector.x;
	y += vector.y;
	if (x < 0 || x > w) {
		vector.x = vector.x * -1;
	}
	if (y<0 || y>h) {
		vector.y = vector.y * -1;
	}
}
