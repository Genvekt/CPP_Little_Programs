#pragma once
#include "Poligon.h"
#include <string>
using namespace std;


class App
{
public:
	App();
	~App();
	void update();
	void draw();
private:
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	Poligon poligon;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;
	SDL_Texture* point_tex;
	void ApplySurface(SDL_Rect* pos, SDL_Texture* tex, SDL_Renderer* rend);
	int DrawTriangulation();
	bool is_inside(Point* a, Point* b, Point* c, Point* p);
	float area(Point* a, Point* b, Point* c);
	void draw_triandle(Point* a, Point* b, Point* c);
	SDL_Texture* LoadImage(std::string file);
	bool is_inside_poligon(int x1, int y1);
	bool does_intersect(int p1_x, int p1_y, int p2_x, int p2_y, int a1_x, int a1_y, int a2_x, int a2_y);
	bool onSegment(int p1_x, int p1_y, int p2_x, int p2_y, int a1_x, int a1_y);

	int orientation(int p1_x, int p1_y, int p2_x, int p2_y, int a1_x, int a1_y);
	
};


