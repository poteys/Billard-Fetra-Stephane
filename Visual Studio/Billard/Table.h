#pragma once
#include "../lib_Point/Point.h"


class Table
{
private:
	int width; //Window width
	int	height; //Window height
	int radius; //Holes radius
	Point holes [6];


public:
	Table();
	Table(int width, int height);

	int getHoleRadius();
	Point* getHolesPosition();
	void displayHoles(SDL_Renderer* renderer);


	void draw(SDL_Renderer* renderer);
};

