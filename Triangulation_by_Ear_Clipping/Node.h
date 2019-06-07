#pragma once
#include "Point.h"
class Node
{
public:
	Node();
	Point* point;
	Node* next;
	Node* previous;
	~Node();
};

