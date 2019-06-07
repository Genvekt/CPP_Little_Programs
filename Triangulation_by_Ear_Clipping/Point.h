#pragma once
#include "SDL.h"
class Point
{
public:
	Point(int x, int y);
	~Point();
	SDL_Rect pos;
	SDL_Texture* texture;
	Point* next;
	Point* previous;
	void connect(Point* next, Point* previous);
};

