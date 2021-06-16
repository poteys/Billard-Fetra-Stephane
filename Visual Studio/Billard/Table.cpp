#include "Table.h"

Table::Table()
{
	this->height = 0;
	this->width = 0;
	this->radius = 0;
}

Table::Table(int width, int height)
{
	this->width = width;
	this->height = height;
	this->radius = 20;
}


void Table::displayHoles(SDL_Renderer* renderer)
{
	//Position holes
	holes[0] = Point(28, 28);	//Top left
	holes[1] = Point(this->width - 28, 28); //Top right

	holes[2] = Point(28, this->height - 28); //Bottom left
	holes[3] = Point(this->width - 28, this->height - 28); //Bottom right

	holes[4] = Point(28, this->height / 2); //Middle left
	holes[5] = Point(this->width - 28, this->height / 2); //Middle right
	
	//Draw holes
	for (int i = 0; i < 6; i++) {
		this->holes[i].draw(renderer, Color(255, 0, 255, SDL_ALPHA_OPAQUE), 0);
		this->holes[i].drawCircle(renderer, this->radius, Color(255, 0, 255, SDL_ALPHA_OPAQUE), true);
	}
}

void Table::draw(SDL_Renderer* renderer)
{
	displayHoles(renderer);
}

Point* Table::getHolesPosition()
{
	return this->holes;
}

int Table::getHoleRadius()
{
	return this->radius;
}
