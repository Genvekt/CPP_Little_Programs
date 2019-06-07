#include "Poligon.h"
#include <iostream>
using namespace std;

Poligon::Poligon()
{
	this->first = nullptr;
	this->last = nullptr;
	size = 0;
}


Poligon::~Poligon()
{

}

void Poligon::add(Point* new_point)
{
	
	if (this->first == nullptr) {
		first = new_point;
		last = new_point;
		first->next = last;
		first->previous = last;
		last->previous = first;
		last->next = first;
		
	}
	else {
		new_point->connect(this->first, this->last);
		this->last = new_point;
	}
	size++;
	display_all();
}

void Poligon::display_all()
{
	cout << "Points \n";
	int id = 0;
	Point* point = first;
	while (id < size) {
		cout << point->pos.x << " " << point->pos.y << "\n";
		point = point->next;
		id++;
	}
}
