#include "Player.h"

Player::Player(Queue* queue)
{
	this->queue = queue;
	this->ballType = "any";
	this->turn = false;
	this->foul = false;
	this->totalBall = 7;
}

void Player::setPlayerBalls(string ballType)
{
	this->ballType = ballType;
}

string& Player::getPlayerBallsType()
{
	return this->ballType;
}

void Player::setTurn(bool turn)
{
	this->turn = turn;
	if (turn == true) {
		this->makeQueuePlayable();
	}
	else {
		this->makeQueueSatic();
	}
}

void Player::setFoul(bool foul)
{
	this->foul = foul;
}

bool Player::isFoul()
{
	return this->foul;
}

void Player::decrementTotalBall()
{
	this->totalBall--;
}

int& Player::getTotalBall()
{
	return this->totalBall;
}

void Player::setQueue(Queue* queue)
{
	this->queue = queue;
}

Queue* Player::getQueue()
{
	return this->queue;
}

void Player::makeQueueSatic()
{
	this->queue->makeStatic();
}

void Player::makeQueuePlayable()
{
	this->queue->makePlayable();
}

bool Player::isTurn()
{
	return this->turn;
}
