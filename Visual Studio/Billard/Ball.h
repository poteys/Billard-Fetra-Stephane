#pragma once
#include "../lib_Point/Point.h"
#include "Queue.h"
#include "Table.h"
#include <string>
using namespace std;

class Ball
{
private:
	string type;

	double mass; //kg
	Point center;
	int radius; //pixel
	Vector speed;
	Vector propulsion;
	Vector acceleration;
	Vector friction; //Friction de la table probablement

	bool ballIsMoving;

	Table trouBillard;


	__time64_t lastUpdate;	//	date in nanoseconds since last update
	__time64_t getTimeInNanoSeconds();

	int width, height;


	double distance(Point ballCenter, Point holeCenter);
	double findNearestHoleDistance(Table& table);

	int sign(double a);

public:
	bool wasHit;

	Ball(double mass, Point center, int radius, int width, int height);
	void update(SDL_Event& event, Queue* queue[], Vector queueSpeed);

	void setPosition(Point position);

	void setType(string ballType);
	string getType();

	Point& getCenter();

	void setSize(int newSize);

	void listenForQueueHit(Queue* queue[], Vector& queueSpeed);
	void listenForBallCollision(Ball* ball, Vector& ballSpeed);


	void setPropulsion(Vector newPropulsion);
	Vector& getPropulsion();


	void setSpeed(Vector queueSpeed);
	void setSpeedX(Vector speed);
	void setSpeedY(Vector speed);
	Vector& getSpeed();

	void setAcceleration(Vector acceleration);

	Vector& computeFriction();


	bool isHitBy(Queue* queue);
	bool isHitBy(Ball* ball);

	Vector getVectorPerpendicularToBallSpeed();


	bool fallInside(Table table);

	void checkBordersAndDrawBall(SDL_Renderer* renderer, const Color& color);


	void visualizeVectorSpeed(SDL_Renderer* renderer);
	void visualizePath(Queue* queue, SDL_Renderer* renderer);


	void draw(SDL_Renderer* renderer, Color color, SDL_Event& event, Queue* queue[], Vector queueSpeed);


};

