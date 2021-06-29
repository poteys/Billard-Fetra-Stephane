#include "Ball.h"
#include "Table.h"
#include <time.h>
#include <iostream>



Ball::Ball(double mass, Point center, int radius, int width, int height)
	: center(center), speed(0, 0), acceleration(0, 0), propulsion(0, 0), friction(0, 0)
{
	this->mass = mass;
	this->radius = radius;
	this->width = width;
	this->height = height;
	this->ballIsMoving = false;
	this->lastUpdate = this->getTimeInNanoSeconds();
	this->wasHit = false;
}

void Ball::update(SDL_Event& event, Queue* queue[], Vector queueSpeed)
{
	__time64_t currentUpdate = this->getTimeInNanoSeconds();


	//	compute elapsed time (in seconds) since last position change
	double deltaT = (currentUpdate - this->lastUpdate) / 1e9;
	this->lastUpdate = currentUpdate;

	//	compute new position of object now
	this->center.x = this->center.x + this->speed.x * deltaT;
	this->center.y = this->center.y + this->speed.y * deltaT;

	//	compute new speed of object now
	this->speed.x = this->speed.x + this->acceleration.x * deltaT;
	this->speed.y = this->speed.y + this->acceleration.y * deltaT;

	//	compute sum of forces pallyed on object
	Vector gravity(0, 0 * this->mass);		  //Activate gravity
	Vector propulsion(this->getPropulsion()); //Increase acceleration

	Vector friction(this->computeFriction()); //Decrease the speed gradually if no acceleration
	Vector sum = propulsion + friction;

	// compute new acceleration of object now
	this->acceleration.x = sum.x / mass;
	this->acceleration.y = sum.y / mass;

	listenForQueueHit(queue, queueSpeed);
}

void Ball::setType(string ballType)
{
	this->type = ballType;
}

string Ball::getType()
{
	return this->type;
}


double Ball::findNearestHoleDistance(Table& table)
{
	double holeDistance = distance(table.getHolesPosition()[0], this->getCenter());
	double minDistance = holeDistance;

	for (int i = 1; i < 6; i++) {
		holeDistance = distance(table.getHolesPosition()[i], this->getCenter());
		if (holeDistance < minDistance) {
			minDistance = holeDistance;
		}
	}
	return minDistance;
}

int Ball::sign(double a)
{
	if (a < 0) {
		return -1;
	}
	else
		return 1;
}


double Ball::distance(Point ballCenter, Point holeCenter)
{
	double distance = sqrt((ballCenter.x - holeCenter.x) * (ballCenter.x - holeCenter.x) +
		(ballCenter.y - holeCenter.y) * (ballCenter.y - holeCenter.y));
	return distance;
}


Point& Ball::getCenter()
{
	return this->center;
}


void Ball::setSize(int newSize)
{
	this->radius = newSize;
}


void Ball::listenForQueueHit(Queue* queue[], Vector& queueSpeed)
{
	int index = -1;
	if (queue[0]->isStaticQueue() == true) {
		index = 1;
	}
	if (queue[1]->isStaticQueue() == true) {
		index = 0;
	}

	if (this->isHitBy(queue[index]) && this->speed.x < 2 && this->speed.y < 2) {
		this->setSpeed(queueSpeed); //Transfer speed to the ball
		this->wasHit = true;
	}
	else if (this->getSpeed().x < 2 && this->getSpeed().y < 2) {
		this->wasHit = false;
	}
}

void Ball::listenForBallCollision(Ball* ball, Vector& ballSpeed)
{
	if (this->isHitBy(ball)) {

		//téta1 et téta2 sont égaux : 45degré
		//v1 = v1prim + v2prim (masses égales)

		//Conservation de l'energie en X
		// v1x		  + v2x		   = v1primX + v2primX
		// ballSpeedX + thisSpeedX = 2 * v1primX  ou 2 *v2primX
		//v1primX = (ballSpeedX + thisSpeedX) / 2   
		//v2primX = (ballSpeedX + thisSpeedX) / 2 //sens contraire à v1primX


		//Conservation de l'energie en Y
		// v1y		  + v2y		   = v1primY + v2primY                 
		// ballSpeedY + thisSpeedY = 2 * v1primY ou  2 *v2primY             =   2 * ballSpeed * cos45  = ballSpeed
		//v1primY = (ballSpeedY + thisSpeedY) / 2		 si this au repos donc thisSpeedY = 0
		//v2primY = (ballSpeedyY+ thisSpeedY) / 2 //même sens que v1primY


		double normeV1 = ballSpeed.magnitude();
		double normeV2 = this->getSpeed().magnitude();

		Vector v2prim(this->getSpeed().x - (ball->getSpeed().x  + this->getSpeed().x) / 2,
			this->getSpeed().y - (ball->getSpeed().y    + this->getSpeed().y) / 2);


		//Vector v2prim (this->getSpeed().x - sin(M_PI / 4) *	1/2 * ball->getSpeed().x,
		//			   this->getSpeed().y - cos(M_PI / 4) *	1/2 * ball->getSpeed().y);
		//		//v2primY = vitesse initiale Y -  cos (téta2) * 1/2 *  v1.x		

		int signV2primX = sign(v2prim.x);
		int signV2primY = sign(v2prim.y);

		Vector v1prim(-signV2primX * ball->getSpeed().x - (ball->getSpeed().x     + this->getSpeed().x) / 2,
			signV2primY * ball->getSpeed().y - (ball->getSpeed().y      + this->getSpeed().y) / 2);


		////Le sens de v1prim en X s'oppose toujours au sens de v2prim en X 
		//Vector v1prim( -signV2primX * ball->getSpeed().x - sin(M_PI / 4) * 1/2 * ball->getSpeed().x,
		//			  signV2primY * ball->getSpeed().y - cos(M_PI / 4) * 1/2 * ball->getSpeed().y);


		this->setSpeed(v2prim);
		ball->setSpeed(v1prim);

	}

}


void Ball::setPropulsion(Vector newPropulsion)
{
	this->propulsion = newPropulsion;
}

Vector& Ball::getPropulsion()
{
	return this->propulsion;
}


void Ball::setSpeed(Vector queueSpeed)
{
	this->speed = queueSpeed;
}

void Ball::setSpeedX(Vector speed)
{
	this->speed.x = speed.x;
}

void Ball::setSpeedY(Vector speed)
{
	this->speed.y = speed.y;
}


Vector& Ball::getSpeed()
{
	return this->speed;
}

void Ball::setAcceleration(Vector acceleration)
{
	this->acceleration = acceleration;
}

Vector& Ball::computeFriction()
{
	//The higher the constant, the quicker the ball will stop
	this->friction.x = .2 * -this->getSpeed().x;
	this->friction.y = .2 * -this->getSpeed().y;

	return this->friction;
}

bool Ball::isHitBy(Queue* queue)
{
	double distance = sqrt((queue->getQueueTip().x - this->center.x)
		* (queue->getQueueTip().x - this->center.x) +
		(queue->getQueueTip().y - this->center.y)
		* (queue->getQueueTip().y - this->center.y));

	//std::cout << distance << std::endl;
	return distance <= this->radius;

}

bool Ball::isHitBy(Ball* ball)
{
	double distance = sqrt((ball->center.x - this->center.x)
		* (ball->center.x - this->center.x) +
		(ball->center.y - this->center.y)
		* (ball->center.y - this->center.y));

	return distance <= 2.0 * this->radius;
}


Vector Ball::getVectorPerpendicularToBallSpeed()
{
	Point perp(this->center.x + cos(M_PI / 2 + this->speed.x * M_PI / 180) * 250,
		this->center.y - sin(M_PI / 2 + this->speed.y * M_PI / 180) * 250);
	Vector p(this->center, perp);
	return p;
}


bool Ball::fallInside(Table table)
{
	double nearestHoleDistance = findNearestHoleDistance(table);
	return nearestHoleDistance <= table.getHoleRadius();
}


void Ball::visualizePath(Queue* queue, SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 70, 100, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer, this->center.x,
		this->center.y,
		this->center.x + cos((180 + queue->getTurn()) * M_PI / 180) * 250,
		this->center.y - sin((180 + queue->getTurn()) * M_PI / 180) * 250);
}


void Ball::checkBordersAndDrawBall(SDL_Renderer* renderer, const Color& color)
{
	//	check borders of screen //Friction is function to speed so compute speed before friction
	if ((this->center.x + this->radius > this->width && this->speed.x > 0) ||
		(this->center.x - this->radius < 0 && this->speed.x < 0)) {
		this->speed.x *= -0.5;
	}
	if ((this->center.y + this->radius > this->height && this->speed.y > 0) ||
		(this->center.y - this->radius < 0 && this->speed.y < 0)) {
		this->speed.y *= -0.5;
	}

	//this->center.draw(renderer, color, 3);
	this->center.drawCircle(renderer, this->radius, color, true);
}


void Ball::visualizeVectorSpeed(SDL_Renderer* renderer)
{
	SDL_RenderDrawLine(renderer, this->center.x, this->center.y,
		this->speed.x + this->center.x, this->speed.y + this->center.y);
}


void Ball::draw(SDL_Renderer* renderer, Color color, SDL_Event& event, Queue* queue[], Vector queueSpeed)
{
	this->update(event, queue, queueSpeed);
	checkBordersAndDrawBall(renderer, color);
	//visualizeVectorSpeed(renderer);

	//SDL_RenderDrawLine(renderer, this->center.x,
	//	this->center.y,
	//	this->center.x + getVectorPerpendicularToBallSpeed().x ,
	//	this->center.y - getVectorPerpendicularToBallSpeed().y);
}


__time64_t Ball::getTimeInNanoSeconds()
{
	struct _timespec64 ts;
	if (_timespec64_get(&ts, TIME_UTC) == 0) {
		throw 0;
	}

	return ts.tv_sec * 1000000000 + ts.tv_nsec;
	//Nombre de nanosec écoulé depuis le 1er janvier 70
}

