#pragma once
#include "../lib_Point/Point.h"


class TableBillard
{
private:
	int width, height;
	Point trouTable;

public:
	TableBillard();
	TableBillard(Point trouTable);
	void draw(SDL_Renderer* renderer, Color color, SDL_Event& event);

	Point getPositionTrou();

};

