#include "Player.h"

Player::Player(Queue* queue)
{
	this->queue = queue;
	this->ballType = "any";
	this->turn = false;
	this->fool = false;
}

void Player::setPlayerBalls(string ballType)
{
	this->ballType = ballType;
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

void Player::setFool(bool fool)
{
	this->fool = fool;
}

void Player::setQueue(Queue* queue)
{
	this->queue = queue;
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
