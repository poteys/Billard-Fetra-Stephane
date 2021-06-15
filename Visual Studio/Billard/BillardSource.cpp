#include <iostream>
using namespace std;

#include <SDL.h>
#include "Queue.h"

constexpr auto MAX_OBJECTS = 10;

//	****************  //
//	window attributs  //
//	****************  //
//	- position and size on screen
constexpr auto POS_X = 500, POS_Y = 200;
constexpr auto WIDTH = 400, HEIGHT = 800;
constexpr auto MAX_BALL = 14;


//	include desired header files for libraries
#include <time.h>
#include "Ball.h"
#include "BillardSource.h"
#include "TableBillard.h"

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


//int findNearestBallIndex(Ball* ball[], Queue& queue)
//{
//	double minDistance = sqrDistance(ball[0]->getCenter(), queue.getQueueTip());
//	int minIndex = 1;
//	for (int i = 0; i < 2; i++) {
//		double ballToTestDistance = sqrDistance(ball[i]->getCenter(), queue.getQueueTip());
//
//		if (ballToTestDistance < minDistance) {
//			minDistance = ballToTestDistance;
//			minIndex = i;
//		}
//	}
//	return minIndex;
//}

void displayTrou(TableBillard* trouBillard[6])
{
	for (int i = 0; i < 6; i++) {
		trouBillard[0] = new TableBillard(Point(28, 28));
		trouBillard[1] = new TableBillard(Point(28, HEIGHT - 28));
		trouBillard[2] = new TableBillard(Point(WIDTH - 20, 28));
		trouBillard[3] = new TableBillard(Point(WIDTH - 20, HEIGHT - 28));
		trouBillard[4] = new TableBillard(Point(28, HEIGHT/2 ));
		trouBillard[5] = new TableBillard(Point(WIDTH-20, HEIGHT/2));
	}
}

//	entry point of application
int main(int argc, char** argv) {
	SDL_Renderer* renderer = init_SDL("Billard game");	//	this object will draw in our window

	/*	prepare useful objects here	*/
	//La queue
	Color queueColor(150, 75, 0, SDL_ALPHA_OPAQUE);
	Queue queue(0.5, -90, Point(WIDTH / 2, HEIGHT - 20, true), Point(WIDTH / 2, HEIGHT - 20.0), WIDTH, HEIGHT);

	TableBillard* trousBillard[6];
	displayTrou(trousBillard);

	//LesBoules
	Color ballColor1(255, 255, 255, SDL_ALPHA_OPAQUE);
	Color ballColor2(0, 0, 0, SDL_ALPHA_OPAQUE);
	Ball* balls[15];
	int numberOfBalls = 15;
	int nombreLigne = 5;

	for (int i = 0; i < numberOfBalls; i++) {
		balls[i] = new Ball(0.5, Point(WIDTH /2, HEIGHT / 10 + 30 * i), 15, WIDTH, HEIGHT);
	}

	long time = clock();



	//	*********  //
	//	main loop  //
	//	*********  //
	bool endOfGame = false;
	while (!endOfGame) {
		//	******************************  //
		//	draw image in rendering buffer  //
		//	******************************  //
		clearWindow(renderer);

		/*	draw any desired graphical objects here	*/

		//	****************  //
		//	event management  //
		//	****************  //
		SDL_Event event = getNextEvent();

		queue.draw(renderer, queueColor, event);
		for (int j = 0; j < nombreLigne; j++) {
			for (int i = 0; i < numberOfBalls; i++) {
				balls[i]->draw(renderer, ballColor2, event, queue, queue.getPropulsion());
			}
		}

		//For balls self collide
		/*for (Ball* ball : ball) {
			ball->listenForHit(ball, ball->getSpeed());
		}*/
		//ball[0]->listenForHit(ball[1], ball[1]->getSpeed());
		//ball[1]->listenForHit(ball[0], ball[0]->getSpeed());


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

		//trou billard
		for (int i = 0; i < 6; i++) {
			trousBillard[i]->draw(renderer, Color(255, 0, 255, SDL_ALPHA_OPAQUE), event);

		}


		for (int j = 0; j < numberOfBalls; j++) {
			for (int i = 0; i < 6; i++) {
				if (balls[j]->touch(trousBillard[i])) {
					delete balls[j];
					balls[j] = balls[numberOfBalls - 1];
					numberOfBalls--;
				}
			}
		}


		showRenderingBuffer(renderer);
		endOfGame = keypressed(event, '\033');
		//SDL_KeyCode;
	}

	time = clock() - time;

	quit_SDL();

	return 0;
}