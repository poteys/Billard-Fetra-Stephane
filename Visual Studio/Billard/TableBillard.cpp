#include "TableBillard.h"

TableBillard::TableBillard()
{
	this->height = 0;
	this->width = 0;
}

TableBillard::TableBillard(Point trouTable) : trouTable(trouTable)
{
}

void TableBillard::draw(SDL_Renderer* renderer, Color color, SDL_Event& event)
{
	this->trouTable.update(event);
	trouTable.drawCircle(renderer, 20, color, true);
}
