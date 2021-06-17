#include <iostream>
#include <time.h>
using namespace std;

#include <SDL.h>
#include "Queue.h"
#include "Ball.h"
#include "BillardSource.h"
#include "Table.h"
#include "Player.h"

constexpr auto POS_X = 500, POS_Y = 200;
constexpr auto WIDTH = 400, HEIGHT = 800;
constexpr auto QUEUE_MASS = 0.5;
constexpr auto QUEUE_INITIAL_ANGLE = -90;
constexpr auto BALL_MASS = 0.5;
constexpr auto BALL_RADIUS = 12;
constexpr auto NUMBER_OF_BALLS = 16; //is 16

enum {
	RAYEE1, PLEINE1, RAYEE2, RAYEE3, NOIR, PLEINE2, PLEINE3, RAYEE4, PLEINE4, RAYEE5,
	RAYEE6, PLEINE5, RAYEE7, PLEINE6, PLEINE7, BLANC
};


SDL_Renderer* init_SDL(const char* title) {
#pragma region SDL initialization
	// SDL initialization
	SDL_Window* window = NULL;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "ERREUR : can't initialize SDL!" << endl;
		exit(0);
	}

	//SDL_ShowCursor(SDL_DISABLE);	//	hide mouse cursor
	SDL_ShowCursor(SDL_ENABLE);	//	show mouse cursor

	//	create the window and its associated renderer
	window = SDL_CreateWindow(title, POS_X, POS_Y, WIDTH, HEIGHT, 0);
	return SDL_CreateRenderer(window, 0, 0);
#pragma endregion
}

void clearWindow(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 30, 80, 35, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
}

void showRenderingBuffer(SDL_Renderer* renderer) {
	SDL_RenderPresent(renderer);
}

SDL_Event getNextEvent() {
	SDL_Event event;
	SDL_PollEvent(&event);

	return event;
}

bool keypressed(SDL_Event& event, char key) {
	return event.type == SDL_KEYDOWN && event.key.keysym.sym == key;
}

void quit_SDL() {
#pragma region SDL quit
	//	quit SDL
	SDL_Quit();
#pragma endregion
}

double sqrDistance(Point a, Point b) {
	double sqrDistance = 0;
	double dx = a.x - b.x;
	double dy = a.y - b.y;
	sqrDistance = dx * dx + dy * dy;
	return sqrDistance;
}

void positionBalls(Ball* balls[], SDL_Renderer* renderer, const Color& ballColor2)
{
	//Position of the first ball
	int x = WIDTH / 2;
	int y = WIDTH / 2;
	int currenIndex = 0;
	int ballsToCreate = 0;
	int maxIndex = 0;

#pragma region POSITION BALLS
	for (int row = 0; row < 5; row++) {
		ballsToCreate = row + 1;
		maxIndex = currenIndex + ballsToCreate;
		for (int index = currenIndex; index < maxIndex; index++) {
			if (index == 0) {
				balls[index] = new Ball(BALL_MASS, Point(x + 0 * BALL_RADIUS, y), BALL_RADIUS, WIDTH, HEIGHT);
				balls[index]->setType("ray�e");
			}


			if (index == 1) {
				balls[index] = new Ball(BALL_MASS, Point(x - row * BALL_RADIUS - 2, y), BALL_RADIUS, WIDTH, HEIGHT);
				balls[index]->setType("pleine");
			}
			if (index == 2) {
				balls[index] = new Ball(BALL_MASS, Point(x + row * BALL_RADIUS + 2, y), BALL_RADIUS, WIDTH, HEIGHT);
				balls[index]->setType("ray�e");
			}


			if (index == 3) {
				balls[index] = new Ball(BALL_MASS, Point(x - row * BALL_RADIUS - 3, y), BALL_RADIUS, WIDTH, HEIGHT);
				balls[index]->setType("ray�e");
			}
			//Le noir au milieu au row = 3
			if (index == NOIR) {
				balls[NOIR] = new Ball(BALL_MASS, Point(x + 0 * BALL_RADIUS, y), BALL_RADIUS, WIDTH, HEIGHT);
				balls[index]->setType("noir");
			}
			if (index == 5) {
				balls[index] = new Ball(BALL_MASS, Point(x + row * BALL_RADIUS + 3, y), BALL_RADIUS, WIDTH, HEIGHT);
				balls[index]->setType("pleine");
			}


			if (index == 6) {
				balls[index] = new Ball(BALL_MASS, Point(x - row * BALL_RADIUS - 6, y), BALL_RADIUS, WIDTH, HEIGHT);
				balls[index]->setType("pleine");
			}
			if (index == 7) {
				balls[index] = new Ball(BALL_MASS, Point(x - 1 * BALL_RADIUS - 2, y), BALL_RADIUS, WIDTH, HEIGHT);
				balls[index]->setType("ray�e");
			}
			if (index == 8) {
				balls[index] = new Ball(BALL_MASS, Point(x + 1 * BALL_RADIUS + 2, y), BALL_RADIUS, WIDTH, HEIGHT);
				balls[index]->setType("pleine");
			}
			if (index == 9) {
				balls[index] = new Ball(BALL_MASS, Point(x + row * BALL_RADIUS + 6, y), BALL_RADIUS, WIDTH, HEIGHT);
				balls[index]->setType("ray�e");
			}


			if (index == 10) {
				balls[index] = new Ball(BALL_MASS, Point(x - row * BALL_RADIUS - 6, y), BALL_RADIUS, WIDTH, HEIGHT);
				balls[index]->setType("ray�e");
			}
			if (index == 11) {
				balls[index] = new Ball(BALL_MASS, Point(x - 2 * BALL_RADIUS - 3, y), BALL_RADIUS, WIDTH, HEIGHT);
				balls[index]->setType("pleine");
			}
			if (index == 12) {
				balls[index] = new Ball(BALL_MASS, Point(x - 0 * BALL_RADIUS, y), BALL_RADIUS, WIDTH, HEIGHT);
				balls[index]->setType("ray�e");
			}
			if (index == 13) {
				balls[index] = new Ball(BALL_MASS, Point(x + 2 * BALL_RADIUS + 3, y), BALL_RADIUS, WIDTH, HEIGHT);
				balls[index]->setType("pleine");
			}
			if (index == 14) {
				balls[index] = new Ball(BALL_MASS, Point(x + row * BALL_RADIUS + 6, y), BALL_RADIUS, WIDTH, HEIGHT);
				balls[index]->setType("pleine");
			}
		}
		currenIndex = maxIndex;
		y += 2 * BALL_RADIUS + 5; //Go to nextLine
	}
	//Main White ball
	balls[BLANC] = new Ball(BALL_MASS, Point(x, 3 * HEIGHT / 4, true), BALL_RADIUS, WIDTH, HEIGHT);
	balls[BLANC]->setType("blanc");
}
#pragma endregion

void visualizeBallPath(Player* players[], Ball* balls[], Queue* queue[], int numberOfBalls, SDL_Renderer* renderer)
{
	int index = -1;
	if (players[0]->isTurn() == true) {
		index = 0;
	}
	if (players[1]->isTurn() == true) {
		index = 1;
	}
	double minDistance = sqrDistance(balls[index]->getCenter(), queue[index]->getQueueTip());
	int minIndex = 0;
	for (int i = 0; i < numberOfBalls; i++) {
		double ballToTestDistance = sqrDistance(balls[i]->getCenter(), queue[index]->getQueueTip());
		if (ballToTestDistance < minDistance) {
			minDistance = ballToTestDistance;
			minIndex = i;
		}
	}

	balls[minIndex]->visualizePath(queue[index], renderer);

}

void displayQueue(Queue* queues[], SDL_Renderer* renderer, const Color& queueColor, SDL_Event& event)
{
	queues[0]->draw(renderer, queueColor, event);
	queues[1]->draw(renderer, queueColor, event);
}

void removeBallInsideHole(Player* players[], int& numberOfBalls, Ball* balls[], const Table& table)
{
	int index = -1;
	if (players[0]->isTurn() == true) {
		index = 0;
	}
	if (players[1]->isTurn() == true) {
		index = 1;
	}

	for (int j = 0; j < numberOfBalls; j++) {
		/*for (int i = 0; i < 6; i++) {*/
		if (balls[j]->fallInside(table)) {
			delete balls[j];
			balls[j] = balls[numberOfBalls - 1];
			numberOfBalls--;
			//players[index]->setPlayerBalls(balls[j]->getType()); //TO DO

			players[1]->setTurn(true);
			players[0]->setTurn(false); //TO DO
		}
		/*}*/
	}
	if (numberOfBalls == 0) {
		quit_SDL();
	}
}

void displayTable(Table& table, SDL_Renderer* renderer)
{
	table.draw(renderer);
}

void listenForBallCollision(int numberOfBalls, Ball* balls[])
{
	for (int currentIndex = 0; currentIndex < numberOfBalls; currentIndex++) {
		for (int indexToCollide = 0; indexToCollide < numberOfBalls; indexToCollide++) {
			if (currentIndex != indexToCollide) { //Listen for other balls collision except the 
				balls[currentIndex]->listenForBallCollision(balls[indexToCollide], balls[indexToCollide]->getSpeed());
			}
		}
	}
}


void displayBalls(Player* players[], int numberOfBalls, Ball* balls[], SDL_Renderer* renderer, SDL_Event& event, Queue* queue[])
{
	int index = -1;
	if (players[0]->isTurn() == true) {
		index = 0;
	}
	if (players[1]->isTurn() == true) {
		index = 1;
	}
	for (int i = 0; i < numberOfBalls; i++) {
		if (i == BLANC) {
			Color color(255, 255, 255, SDL_ALPHA_OPAQUE);
			balls[i]->draw(renderer, color, event, queue, queue[index]->getPropulsion());
		}
		if (i == NOIR) {
			Color color(0, 0, 0, SDL_ALPHA_OPAQUE);
			balls[i]->draw(renderer, color, event, queue, queue[index]->getPropulsion());
		}
		if (i == RAYEE1 || i == RAYEE2 || i == RAYEE3 || i == RAYEE4 || i == RAYEE5 || i == RAYEE6 || i == RAYEE7) {
			Color color(255, 0, 0, SDL_ALPHA_OPAQUE);
			balls[i]->draw(renderer, color, event, queue, queue[index]->getPropulsion());
		}
		if (i == PLEINE1 || i == PLEINE2 || i == PLEINE3 || i == PLEINE4 || i == PLEINE5 || i == PLEINE6 || i == PLEINE7) {
			Color color(10, 100, 255, SDL_ALPHA_OPAQUE);
			balls[i]->draw(renderer, color, event, queue, queue[index]->getPropulsion());
		}
	}
}

int main(int argc, char** argv) {
	SDL_Renderer* renderer = init_SDL("Billard game");

	//Preparing all objects
	Color queueColor(150, 75, 0, SDL_ALPHA_OPAQUE);
	//Queue queue1(QUEUE_MASS, QUEUE_INITIAL_ANGLE, tipPosition, handlePosition, WIDTH, HEIGHT);
	Queue* queues[2];
	for (int i = 0; i < 2; i++) {
		Point tipPosition(WIDTH / 2 - 100 * i, HEIGHT - 100.0);
		Point handlePosition(WIDTH / 2 - 100 * i, HEIGHT - 20.0);
		queues[i] = new Queue(QUEUE_MASS, QUEUE_INITIAL_ANGLE, tipPosition, handlePosition, WIDTH, HEIGHT);
	}


	Table table(WIDTH, HEIGHT);



	Color ballColor1(255, 255, 255, SDL_ALPHA_OPAQUE);
	Color ballColor2(0, 0, 0, SDL_ALPHA_OPAQUE);
	int numberOfBalls = NUMBER_OF_BALLS;
	Ball* balls[NUMBER_OF_BALLS];
	positionBalls(balls, renderer, ballColor2);



	Player* players[2];
	players[0] = new Player(queues[0]);
	players[0]->setTurn(true);

	players[1] = new Player(queues[1]);
	players[1]->setTurn(false);


	bool endOfGame = false;
	while (!endOfGame) {

		clearWindow(renderer);
		SDL_Event event = getNextEvent();

		displayTable(table, renderer);
		displayBalls(players, numberOfBalls, balls, renderer, event, queues);
		displayQueue(queues, renderer, queueColor, event);

		visualizeBallPath(players, balls, queues, numberOfBalls, renderer);
		listenForBallCollision(numberOfBalls, balls);
		removeBallInsideHole(players, numberOfBalls, balls, table);

		showRenderingBuffer(renderer);
		endOfGame = keypressed(event, '\033');
	}

	quit_SDL();

	return 0;
}