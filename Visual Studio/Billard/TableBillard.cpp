#include "TableBillard.h"

//TableBillard::TableBillard()
//{
//	this->height = 0;
//	this->width = 0;
//	this->rayon = 0;
//}

TableBillard::TableBillard(Point trouTable) : trouTable(trouTable), rayon(0), height(0), width(0)
{
}

void TableBillard::draw(SDL_Renderer* renderer, Color color, SDL_Event& event)
{
	this->trouTable.update(event);
	this->rayon = 20;
	trouTable.drawCircle(renderer, this->rayon, color, true);
}

Point TableBillard::getPositionTrou()
{
	return this->trouTable;
}

int TableBillard::getRayon()
{
	return this->rayon;
}
