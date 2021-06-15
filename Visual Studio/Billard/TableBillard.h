#pragma once
#include "../lib_Point/Point.h"


class TableBillard
{
private:
	int width, height, rayon;
	Point trouTable;

public:
	TableBillard(Point trouTable);
	void draw(SDL_Renderer* renderer, Color color, SDL_Event& event);

	Point getPositionTrou();
	int getRayon();
};

