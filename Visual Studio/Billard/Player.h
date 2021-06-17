#pragma once
#include "Ball.h"
class Player
{
private:

	string ballType;
	bool turn;
	bool fool;

	Queue* queue;

public:
	Player(Queue* queue);

	void setPlayerBalls(string ballType);
	void setTurn(bool turn);
	void setFool(bool fool);

	void setQueue(Queue* queue);

	void makeQueueSatic();
	void makeQueuePlayable();

	bool isTurn();

};

