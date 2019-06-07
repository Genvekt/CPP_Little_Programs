#include "App.h"
#include "Node.h"
#include <stdlib.h>
#include <iostream>
#include <algorithm> 
using namespace std;


App::App()
{
	SCREEN_WIDTH = 500;
	SCREEN_HEIGHT = 500;
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
	point_tex = LoadImage("point.bmp");
}


App::~App()
{
}

void App::update()
{

	bool keep_window_open = true;
	bool update = true;
	while (keep_window_open)
	{
		while (SDL_PollEvent(&event) > 0)
		{
			switch (event.type)
			{
			case SDL_QUIT:
				keep_window_open = false;
				break;

			

			case SDL_MOUSEBUTTONDOWN:
				int mouseX = 0;
				int mouseY = 0;
				SDL_GetMouseState(&mouseX, &mouseY);
				Point* point = (Point*)malloc(sizeof(Point));
				point->pos.x = mouseX;
				point->pos.y = mouseY;
				poligon.display_all();
				poligon.add(point);
				update = true;
			}
		}
		if (update) {
			draw();
			update = false;
		}
		
	}
}

void App::draw()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);
	int current = 0;
	Point* point = poligon.first;
	DrawTriangulation();
	SDL_SetRenderDrawColor(renderer, 0, 100, 255, SDL_ALPHA_OPAQUE);
	while (current < poligon.size) {
		SDL_RenderDrawLine(renderer, point->pos.x, point->pos.y, point->next->pos.x, point->next->pos.y);
		SDL_RenderDrawPoint(renderer, point->pos.x, point->pos.y);
		point = point->next;
		current++;
	}
	
	SDL_RenderPresent(renderer);
}

void App::ApplySurface(SDL_Rect* pos, SDL_Texture* tex, SDL_Renderer* rend)
{
}

SDL_Texture* App::LoadImage(std::string file)
{
	SDL_Surface* loadedImage = nullptr;
	SDL_Texture* texture = nullptr;
	loadedImage = SDL_LoadBMP(file.c_str());
	if (loadedImage != nullptr) {
		texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
		SDL_FreeSurface(loadedImage);
	}
	else
		cout << SDL_GetError() << endl;
	return texture;
}

bool App::is_inside_poligon(int p1_x, int p1_y)
{
	int p2_x = p1_x;
	int p2_y = 1000;
	int count = 0;

	Point* current = poligon.first;
	for (int i = 0; i < poligon.size; i++) {
		if (does_intersect(p1_x, p1_y, p2_x, p2_y, current->pos.x, current->pos.y, current->next->pos.x, current->next->pos.y)) {
			count++;
		}
		current = current->next;
	}
	if (count % 2 == 0) return false;
	
    return true;
}

bool App::does_intersect(int p1_x, int p1_y, int p2_x, int p2_y, int a1_x, int a1_y, int a2_x, int a2_y)
{
	int o1 = orientation(p1_x, p1_y, p2_x, p2_y, a1_x, a1_y);
	int o2 = orientation(p1_x, p1_y, p2_x, p2_y, a2_x, a2_y);
	int o3 = orientation(a1_x, a1_y, a2_x, a2_y, p1_x, p1_y);
	int o4 = orientation(a1_x, a1_y, a2_x, a2_y, p2_x, p2_y);

	if (o1 != o2 && o3 != o4) return true;
	if (o1 == 0 && onSegment(p1_x, p1_y, a1_x, a1_y, p2_x, p2_y)) return true;

	if (o2 == 0 && onSegment(p1_x, p1_y, a2_x, a2_y, p2_x, p2_y)) return true;

	if (o3 == 0 && onSegment(a1_x, a1_y, p1_x, p1_y, a2_x, a2_y)) return true;

	if (o4 == 0 && onSegment(a1_x, a1_y, p2_x, p2_y, a2_x, a2_y)) return true;

	return false; 
	
}

bool App::onSegment(int p1_x, int p1_y, int p2_x, int p2_y, int a1_x, int a1_y)
{
	if (p2_x <= max(p1_x, a1_x) && p2_x >= min(p1_x, a1_x) && p2_y <= max(p1_y, a1_y) && p2_y >= min(p1_y, a1_y)) {
		return true;
	}
	return false;
}

int App::orientation(int p1_x, int p1_y, int p2_x, int p2_y, int a1_x, int a1_y)
{
	int val = (p2_y - p1_y) * (a1_x - p2_x) - (p2_x - p1_x) * (a1_y - p2_y);
	if (val == 0) return 0;
	return (val > 0) ? 1 : 2;
	
}

int App::DrawTriangulation(){
	Node* first_node = nullptr;
	Node* last_node = nullptr;
	Point* current_point = poligon.first;

	int num = poligon.size;
	if (num < 3) {
		return 0;
	}
	
	for (int i = 0; i < num; i++) {
		Node* new_node = (Node*)malloc(sizeof(Node));
		new_node->point = current_point;
		if (first_node == nullptr) {
			first_node = new_node;
			last_node = new_node;
			first_node->previous = last_node;
			first_node->next = last_node;
			last_node->next = first_node;
			last_node->previous = first_node;
		}
		else {
			last_node->next = new_node;
			first_node->previous = new_node;
			new_node->next = first_node;
			new_node->previous = last_node;
			last_node = new_node;
		}
		current_point = current_point->next;
	}

	int trials = 0;
	Node* current = first_node;
	bool is_ear = true;
	while (num >= 3 && trials <= num) {
		Node* a = current->previous;
		Node* b = current;
		Node* c = current->next;
		Node* candidate = c->next;
	
		is_ear = true;
		
		for (int i = 0; i < num - 3; i++) {
			if (is_inside(a->point, b->point, c->point, candidate->point)) {
				is_ear = false;
				break;
			}
			
		}
		if(is_ear) {
			int middle_x = (a->point->pos.x + c->point->pos.x) / 2;
			int middle_y = (a->point->pos.y + c->point->pos.y) / 2;
			if (is_inside_poligon(middle_x, middle_y)) {
				Point* temp = poligon.first;
				for (int i = 0; i < poligon.size; i++) {
					if ((a->point->pos.x != temp->pos.x && a->point->pos.y != temp->pos.y) &&
						(a->point->pos.x != temp->next->pos.x && a->point->pos.y != temp->next->pos.y) &&
						(c->point->pos.x != temp->pos.x && c->point->pos.y != temp->pos.y)&&
						(c->point->pos.x != temp->next->pos.x && c->point->pos.y != temp->next->pos.y) &&
						does_intersect(a->point->pos.x, a->point->pos.y, c->point->pos.x, c->point->pos.y, temp->pos.x, temp->pos.y, temp->next->pos.x, temp->next->pos.y)) {
						is_ear = false;
						break;
					}
					temp = temp->next;
				}
				if (is_ear) {
					draw_triandle(a->point, b->point, c->point);
					a->next = c;
					c->previous = a;
					free(b);
					trials = 0;
					num--;
				}
				else {
					trials++;
				}
				
			}
			else {
				trials++;
			}
		}
		else {
			trials++;
			
		}current = c;
	}
}

bool App::is_inside(Point* a, Point* b, Point* c, Point* p) {
	float A = area(a, b, c);
	float A1 = area(a, b, p);
	float A2 = area(a, c, p);
	float A3 = area(b, c, p);
	return (A - A1 - A2 - A3 > 0.00001);
}

float App::area(Point* a, Point* b, Point* c) {
	return abs((a->pos.x * (b->pos.y - c->pos.y) + b->pos.x * (c->pos.y - a->pos.y) + c->pos.x * (a->pos.y - b->pos.y))/2);
}
void App::draw_triandle(Point* a, Point* b, Point* c) {
	SDL_RenderDrawLine(renderer, a->pos.x, a->pos.y, b->pos.x, b->pos.y);
	SDL_RenderDrawLine(renderer, a->pos.x, a->pos.y, c->pos.x, c->pos.y);
	SDL_RenderDrawLine(renderer, b->pos.x, b->pos.y, c->pos.x, c->pos.y);
}