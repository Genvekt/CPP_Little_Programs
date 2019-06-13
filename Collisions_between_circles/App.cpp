#include "App.h"
#include <iostream>
#include <math.h> 
using namespace std;


App::App()
{
	SCREEN_WIDTH = 1920;
	SCREEN_HEIGHT = 800;
	window = SDL_CreateWindow("",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!window)
	{
		cout << "Failed to create window\n";
		cout << "SDL2 Error: " << SDL_GetError() << "\n";
		return;
	}
	circleText[0] = LoadImage("CircleY.png");
	circleText[1] = LoadImage("CircleO.png");
	circleText[2] = LoadImage("CircleR.png");
	circleText[3] = LoadImage("CircleP.png");
	circleText[4] = LoadImage("CirclePe.png");
	circleText[5] = LoadImage("CircleB.png");
	circleText[6] = LoadImage("CircleBlite.png");
	circleText[7] = LoadImage("CircleG.png");

	for (int i = 0; i < CIRCLES_NUM; i++) {
		circles[i] = (Circle*)malloc(sizeof(Circle));
		circles[i]->x = rand() % SCREEN_WIDTH;
		circles[i]->y = rand() % SCREEN_HEIGHT;
		circles[i]->radius = rand() % 50+50;
		circles[i]->color = 0;

		circles[i]->vector.x = rand() % 20 -10;
		circles[i]->vector.y = rand() % 20 -10;
		
	}
}


App::~App()
{
}

void App::performAllCollisions()
{
	for (int i = 0; i < CIRCLES_NUM - 1; i++) {
		for (int j = i + 1; j < CIRCLES_NUM; j++) {
			if(circles[i]->isCollide(circles[j])) {
				circles[i]->Collide(circles[j]);
				circles[i]->color++;
				if (circles[i]->color == TEXT_NUM) {
					circles[i]->color = 0;
				}
				circles[j]->color++;
				if (circles[j]->color == TEXT_NUM) {
					circles[j]->color = 0;
				}
			}
		}
	}
}

void App::update()
{
	bool keep_window_open = true;
	hasUpdate = true;
	int timer = 0;
	while (keep_window_open)
	{
		while (SDL_PollEvent(&event) > 0)
		{
			switch (event.type)
			{
			case SDL_QUIT:
				keep_window_open = false;
				break;

			}
		}
		timer++;
		if (timer > 10000) {
			hasUpdate = true;
			timer = 0;
		}

		if (hasUpdate) {
			hasUpdate = false;
			performAllCollisions();
			draw();
		}
	}
}

void App::draw()
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_UpdateWindowSurface(window);
	SDL_RenderClear(renderer);
	for (int i = 0; i < CIRCLES_NUM; i++) {
		circles[i]->move(SCREEN_WIDTH, SCREEN_HEIGHT);
		drawCircle(circles[i]);
	}
	SDL_RenderPresent(renderer);
}

SDL_Texture* App::LoadImage(std::string file)
{
	SDL_Surface* loadedImage = nullptr;
	SDL_Texture* texture = nullptr;
	loadedImage = IMG_Load(file.c_str());
	if (loadedImage != nullptr) {
		texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
		SDL_FreeSurface(loadedImage);
	}
	else
		cout << SDL_GetError() << endl;
	return texture;
}

void App::ApplySurface(SDL_Rect* pos, SDL_Texture* tex, SDL_Renderer* rend)
{
	SDL_RenderCopy(rend, tex, NULL, pos);
}

void App::drawCircle(Circle* c)
{
	SDL_Rect pos;
	pos.x = c->x - c->radius;
	pos.y = c->y - c->radius;
	pos.w = 2 * c->radius;
	pos.h = 2 * c->radius;
	ApplySurface(&pos, circleText[c->color], renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer, c->x, c->y, c->x + c->vector.x, c->y + c->vector.y);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
}
