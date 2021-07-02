#pragma once
#include "Ball.h"
class Player
{
private:

	string ballType;

	bool turn;
	bool foul;

	int totalBall;

	Queue* queue;

public:
	Player(Queue* queue);

	void setPlayerBalls(string ballType);
	string& getPlayerBallsType();

	void setTurn(bool turn);

	void setFoul(bool foul);
	bool isFoul();

	void decrementTotalBall();
	int& getTotalBall();

	void setQueue(Queue* queue);
	Queue* getQueue();

	void makeQueueSatic();
	void makeQueuePlayable();

	bool isTurn();

};