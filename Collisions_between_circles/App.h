#pragma once
#include "Circle.h"
#include "SDL.h"
#include "SDL_image.h"
#include <string>
#define CIRCLES_NUM 50
#define TEXT_NUM 8
class App
{
public:
	App();
	~App();
	Circle* circles[CIRCLES_NUM];
	void performAllCollisions();
	void update();
	void draw();
	bool hasUpdate;

	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;
	SDL_Texture* circleText[TEXT_NUM];

	SDL_Texture* LoadImage(std::string file);
	void ApplySurface(SDL_Rect* pos, SDL_Texture* tex, SDL_Renderer* rend);
	void drawCircle(Circle* c);
};

