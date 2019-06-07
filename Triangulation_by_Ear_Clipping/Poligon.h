#pragma once
#include "Point.h"
class Poligon
{
public:
	Poligon();
	~Poligon();
	int size;
	Point* first;
	Point* last;
	void add(Point* new_point);
	void display_all();
};