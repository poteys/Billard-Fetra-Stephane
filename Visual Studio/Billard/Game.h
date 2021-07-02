#pragma once
#include <iostream>
#include "Player.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

using namespace std;
constexpr auto POS_X = 900, POS_Y = 200;
constexpr auto QUEUE_MASS = 0.5;
constexpr auto QUEUE_INITIAL_ANGLE = -90;
constexpr auto BALL_MASS = 0.5;
constexpr auto BALL_RADIUS = 12;
constexpr auto NUMBER_OF_BALLS = 16;

enum {
	RAYEE1, PLEINE1, RAYEE2, RAYEE3, NOIR, PLEINE2, PLEINE3, RAYEE4, PLEINE4, RAYEE5,
	RAYEE6, PLEINE5, RAYEE7, PLEINE6, PLEINE7, BLANC
};

class Game
{
private:
	int width, height;


	const Color BALL_RAYEE = Color(255, 0, 0, SDL_ALPHA_OPAQUE);
	const Color BALL_PLEINE = Color(0, 0, 255, SDL_ALPHA_OPAQUE);
	const Color BALL_BLANC = Color(255, 255, 255, SDL_ALPHA_OPAQUE);
	const Color BALL_NOIR = Color(0, 0, 0, SDL_ALPHA_OPAQUE);


	int numberOfBalls;


	Player* players[2];
	Queue* queues[2];
	Ball* balls[NUMBER_OF_BALLS];
	Table table;


	void initializeTable();
	void initializeQueue();
	void initializeBalls();
	void initializePlayers();


	SDL_Renderer* init_SDL(const char* title);
	void clearWindow(SDL_Renderer* renderer);
	SDL_Event getNextEvent();
	void showRenderingBuffer(SDL_Renderer* renderer);
	bool keypressed(SDL_Event& event, char key);
	void quit_SDL();


	void displayTable(SDL_Renderer* renderer);
	void displayBalls(SDL_Renderer* renderer, SDL_Event& event);
	void displayQueues(SDL_Renderer* renderer, SDL_Event& event);
	double sqrDistance(Point a, Point b);
	int visualizeBallPath(SDL_Renderer* renderer);
	void listenForBallCollision();
	string getAndRemoveBallInsideHole(int& minIndex);


	void displayScreen(SDL_Renderer* renderer, int& minIndex, string& ballInsideHoleType);
	void waitForPlayerHit(SDL_Renderer* renderer, int& minIndex, string& ballInsideHoleType);
	void waitForBallToStop(int& minIndex, SDL_Renderer* renderer, string& ballInsideHoleType);


	bool player1MissesTheHole(std::string& ballInsideHoleType);
	bool player2MissesTheHole(std::string& ballInsideHoleType);
	void switchToPlayer2();
	void switchToPlayer1();
	bool player1InsertedBallRayée(std::string& ballInsideHoleType);
	bool player1InsertedBallPleine(std::string& ballInsideHoleType);
	bool player2InsertedBallRayée(std::string& ballInsideHoleType);
	bool player2InsertedBallPleine(std::string& ballInsideHoleType);

	void player1GotBallsRayées();
	void player1GotBallsPleines();
	void player2GotBallsRayées();
	void player2GotBallsPleines();

	void displayScore();

public:
	bool playersDontHaveSpecificBallType;
	Game(int width, int height);


	void start();


};

