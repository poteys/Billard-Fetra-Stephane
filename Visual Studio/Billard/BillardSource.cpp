#include <iostream>
#include <time.h>
using namespace std;

#include <SDL.h>
#include "Queue.h"
#include "Ball.h"
#include "BillardSource.h"
#include "Table.h"

constexpr auto POS_X = 500, POS_Y = 200;
constexpr auto WIDTH = 400, HEIGHT = 800;
constexpr auto QUEUE_MASS = 0.5;
constexpr auto QUEUE_INITIAL_ANGLE = -90;
constexpr auto BALL_MASS = 0.5;
constexpr auto BALL_RADIUS = 15;


//	include desired header files for libraries


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

void displayBalls(int nombreLigne, int numberOfBalls, Ball* balls[], SDL_Renderer* renderer, const Color& ballColor2, SDL_Event& event, Queue& queue)
{
	for (int j = 0; j < nombreLigne; j++) {
		for (int i = 0; i < numberOfBalls; i++) {
			balls[i]->draw(renderer, ballColor2, event, queue, queue.getPropulsion());
		}
	}
}

void visualizeBallPath(Ball* balls[], Queue& queue, int numberOfBalls, SDL_Renderer* renderer)
{
	double minDistance = sqrDistance(balls[0]->getCenter(), queue.getQueueTip());
	int minIndex = 0;
	for (int i = 0; i < numberOfBalls; i++) {
		double ballToTestDistance = sqrDistance(balls[i]->getCenter(), queue.getQueueTip());
		if (ballToTestDistance < minDistance) {
			minDistance = ballToTestDistance;
			minIndex = i;
		}
	}

	balls[minIndex]->visualizePath(queue, renderer);
}

void displayQueue(Queue& queue, SDL_Renderer* renderer, const Color& queueColor, SDL_Event& event)
{
	queue.draw(renderer, queueColor, event);
}

void removeBallInsideHole(int& numberOfBalls, Ball* balls[], const Table& table)
{
	for (int j = 0; j < numberOfBalls; j++) {
		for (int i = 0; i < 6; i++) {
			if (balls[j]->fallInside(table)) {
				delete balls[j];
				balls[j] = balls[numberOfBalls - 1];
				numberOfBalls--;
			}
		}
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
	for (int i = 1; i < numberOfBalls; i++) {
		balls[0]->listenForBallCollision(balls[i], balls[i]->getSpeed());
	}
}


int main(int argc, char** argv) {
	SDL_Renderer* renderer = init_SDL("Billard game");	


	Color queueColor(150, 75, 0, SDL_ALPHA_OPAQUE);
	Point tipPosition(WIDTH / 2, HEIGHT - 200.0);
	Point handlePosition(WIDTH / 2, HEIGHT - 20.0);
	Queue queue(QUEUE_MASS, QUEUE_INITIAL_ANGLE, tipPosition, handlePosition, WIDTH, HEIGHT);


	Table table(WIDTH, HEIGHT);


	Color ballColor1(255, 255, 255, SDL_ALPHA_OPAQUE);
	Color ballColor2(0, 0, 0, SDL_ALPHA_OPAQUE);
	int numberOfBalls = 15;
	int numberOfRows = 5;
	Ball* balls[15];
	for (int i = 0; i < numberOfBalls; i++) {
		balls[i] = new Ball(BALL_MASS, Point(WIDTH /2, HEIGHT / 10.0 + 30.0 * i), BALL_RADIUS, WIDTH, HEIGHT);
	}


	bool endOfGame = false;
	while (!endOfGame) {

		clearWindow(renderer);
		SDL_Event event = getNextEvent();

		displayTable(table, renderer);
		displayBalls(numberOfRows, numberOfBalls, balls, renderer, ballColor2, event, queue);
		displayQueue(queue, renderer, queueColor, event);

		visualizeBallPath(balls, queue, numberOfBalls, renderer);
		listenForBallCollision(numberOfBalls, balls);
		removeBallInsideHole(numberOfBalls, balls, table);

		showRenderingBuffer(renderer);
		endOfGame = keypressed(event, '\033');
	}

	quit_SDL();

	return 0;
}