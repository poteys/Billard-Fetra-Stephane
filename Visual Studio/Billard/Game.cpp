#include "Game.h"




Game::Game(int width, int height)
{
	this->width = width;
	this->height = height;

	this->numberOfBalls = NUMBER_OF_BALLS;

	this->initializeTable();
	this->initializeQueue();
	this->initializeBalls();
	this->initializePlayers();

	this->playersDontHaveSpecificBallType = true;
}


SDL_Renderer* Game::init_SDL(const char* title)
{
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
	window = SDL_CreateWindow(title, POS_X, POS_Y, this->width, this->height, 0);
	return SDL_CreateRenderer(window, 0, 0);
#pragma endregion
}


void Game::initializeTable()
{
	this->table = Table(this->width, this->height);
}

void Game::initializeBalls() {
	//Position of the first ball
	int x = this->width / 2;
	int y = this->width / 2;
	int currenIndex = 0;
	int ballsToCreate = 0;
	int maxIndex = 0;

#pragma region POSITION BALLS
	for (int row = 0; row < 5; row++) {
		ballsToCreate = row + 1;
		maxIndex = currenIndex + ballsToCreate;
		for (int index = currenIndex; index < maxIndex; index++) {
			if (index == 0) {
				this->balls[index] = new Ball(BALL_MASS, Point(x + 0 * BALL_RADIUS, y), BALL_RADIUS, this->width, this->height);
				this->balls[index]->setType("rayée");
			}


			if (index == 1) {
				this->balls[index] = new Ball(BALL_MASS, Point(x - row * BALL_RADIUS - 2.0, y), BALL_RADIUS, this->width, this->height);
				this->balls[index]->setType("pleine");
			}
			if (index == 2) {
				this->balls[index] = new Ball(BALL_MASS, Point(x + row * BALL_RADIUS + 2.0, y), BALL_RADIUS, this->width, this->height);
				this->balls[index]->setType("rayée");
			}


			if (index == 3) {
				this->balls[index] = new Ball(BALL_MASS, Point(x - row * BALL_RADIUS - 3.0, y), BALL_RADIUS, this->width, this->height);
				this->balls[index]->setType("rayée");
			}
			//Le noir au milieu au row = 3
			if (index == 4) {
				this->balls[NOIR] = new Ball(BALL_MASS, Point(x + 0 * BALL_RADIUS, y), BALL_RADIUS, this->width, this->height);
				this->balls[index]->setType("noir");
			}
			if (index == 5) {
				this->balls[index] = new Ball(BALL_MASS, Point(x + row * BALL_RADIUS + 3.0, y), BALL_RADIUS, this->width, this->height);
				this->balls[index]->setType("pleine");
			}


			if (index == 6) {
				this->balls[index] = new Ball(BALL_MASS, Point(x - row * BALL_RADIUS - 6.0, y), BALL_RADIUS, this->width, this->height);
				this->balls[index]->setType("pleine");
			}
			if (index == 7) {
				this->balls[index] = new Ball(BALL_MASS, Point(x - 1.0 * BALL_RADIUS - 2.0, y), BALL_RADIUS, this->width, this->height);
				this->balls[index]->setType("rayée");
			}
			if (index == 8) {
				this->balls[index] = new Ball(BALL_MASS, Point(x + 1.0 * BALL_RADIUS + 2.0, y), BALL_RADIUS, this->width, this->height);
				this->balls[index]->setType("pleine");
			}
			if (index == 9) {
				this->balls[index] = new Ball(BALL_MASS, Point(x + row * BALL_RADIUS + 6.0, y), BALL_RADIUS, this->width, this->height);
				this->balls[index]->setType("rayée");
			}


			if (index == 10) {
				this->balls[index] = new Ball(BALL_MASS, Point(x - row * BALL_RADIUS - 6.0, y), BALL_RADIUS, this->width, this->height);
				this->balls[index]->setType("rayée");
			}
			if (index == 11) {
				this->balls[index] = new Ball(BALL_MASS, Point(x - 2.0 * BALL_RADIUS - 3.0, y), BALL_RADIUS, this->width, this->height);
				this->balls[index]->setType("pleine");
			}
			if (index == 12) {
				this->balls[index] = new Ball(BALL_MASS, Point(x - 0 * BALL_RADIUS, y), BALL_RADIUS, this->width, this->height);
				this->balls[index]->setType("rayée");
			}
			if (index == 13) {
				this->balls[index] = new Ball(BALL_MASS, Point(x + 2.0 * BALL_RADIUS + 3.0, y), BALL_RADIUS, this->width, this->height);
				this->balls[index]->setType("pleine");
			}
			if (index == 14) {
				this->balls[index] = new Ball(BALL_MASS, Point(x + row * BALL_RADIUS + 6.0, y), BALL_RADIUS, this->width, this->height);
				this->balls[index]->setType("pleine");
			}
		}
		currenIndex = maxIndex;
		y += 2 * BALL_RADIUS + 5; //Go to nextLine
	}
	//Main White ball
	balls[BLANC] = new Ball(BALL_MASS, Point(x, 3 * this->height / 4, true), BALL_RADIUS, this->width, this->height);
	balls[BLANC]->setType("blanc");
}
#pragma endregion


void Game::initializeQueue()
{
	for (int i = 0; i < 2; i++) {
		Point tipPosition(this->width / 2 - 100.0 * i, this->height - 100.0);
		Point handlePosition(this->width / 2 - 100.0 * i, this->height - 20.0);
		this->queues[i] = new Queue(QUEUE_MASS, QUEUE_INITIAL_ANGLE, tipPosition, handlePosition, this->width, this->height);
	}
}


void Game::initializePlayers()
{
	this->players[0] = new Player(this->queues[0]);
	this->players[0]->setTurn(true);
	this->players[1] = new Player(this->queues[1]);
	this->players[1]->setTurn(false);
}

void Game::clearWindow(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 30, 80, 35, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
}

SDL_Event Game::getNextEvent() {
	SDL_Event event;
	SDL_PollEvent(&event);

	return event;
}

void Game::showRenderingBuffer(SDL_Renderer* renderer) {
	SDL_RenderPresent(renderer);
}

bool Game::keypressed(SDL_Event& event, char key) {
	return event.type == SDL_KEYDOWN && event.key.keysym.sym == key;
}


void Game::quit_SDL() {
	SDL_Quit();
}

void Game::displayTable(SDL_Renderer* renderer)
{
	this->table.draw(renderer);
}

void Game::displayBalls(SDL_Renderer* renderer, SDL_Event& event)
{
	int index = -1;
	if (this->players[0]->isTurn() == true) {
		index = 0;
	}
	if (this->players[1]->isTurn() == true) {
		index = 1;
	}
	for (int i = 0; i < numberOfBalls; i++) {
		if (balls[i]->getType() == "blanc") {
			Color color(255, 255, 255, SDL_ALPHA_OPAQUE);
			balls[i]->draw(renderer, BALL_BLANC, event, this->queues, this->queues[index]->getPropulsion());
		}
		if (balls[i]->getType() == "noir") {
			Color color(0, 0, 0, SDL_ALPHA_OPAQUE);
			balls[i]->draw(renderer, BALL_NOIR, event, this->queues, this->queues[index]->getPropulsion());
		}
		if (balls[i]->getType() == "rayée") {
			Color color(255, 0, 0, SDL_ALPHA_OPAQUE);
			balls[i]->draw(renderer, BALL_RAYEE, event, this->queues, this->queues[index]->getPropulsion());
		}
		if (balls[i]->getType() == "pleine") {
			Color color(10, 100, 255, SDL_ALPHA_OPAQUE);
			balls[i]->draw(renderer, BALL_PLEINE, event, this->queues, this->queues[index]->getPropulsion());
		}
	}
}

void Game::displayQueues(SDL_Renderer* renderer, SDL_Event& event)
{
	this->queues[0]->draw(renderer, event);
	this->queues[1]->draw(renderer, event);
}

double Game::sqrDistance(Point a, Point b) {
	double sqrDistance = 0;
	double dx = a.x - b.x;
	double dy = a.y - b.y;
	sqrDistance = dx * dx + dy * dy;
	return sqrDistance;
}


int Game::visualizeBallPath(SDL_Renderer* renderer)
{
	int index = -1;
	if (this->players[0]->isTurn() == true) {
		index = 0;
	}
	if (this->players[1]->isTurn() == true) {
		index = 1;
	}
	double minDistance = sqrDistance(balls[index]->getCenter(), this->queues[index]->getQueueTip());
	int minIndex = 0;
	for (int i = 0; i < this->numberOfBalls; i++) {
		double ballToTestDistance = sqrDistance(this->balls[i]->getCenter(), this->queues[index]->getQueueTip());
		if (ballToTestDistance < minDistance) {
			minDistance = ballToTestDistance;
			minIndex = i;
		}
	}
	this->balls[minIndex]->visualizePath(this->queues[index], renderer);

	return minIndex;
}

void Game::listenForBallCollision()
{
	for (int currentIndex = 0; currentIndex < this->numberOfBalls; currentIndex++) {
		for (int indexToCollide = 0; indexToCollide < this->numberOfBalls; indexToCollide++) {
			if (currentIndex != indexToCollide) { //Listen for other balls collision except the for the current ball
				this->balls[currentIndex]->listenForBallCollision(this->balls[indexToCollide], this->balls[indexToCollide]->getSpeed());
			}
		}
	}
}

string Game::getAndRemoveBallInsideHole(int& minIndex)
{
	int index = -1;
	if (this->players[0]->isTurn() == true) {
		index = 0;
	}
	if (this->players[1]->isTurn() == true) {
		index = 1;
	}

	string ballInsideHoleType = "";

	for (int j = 0; j < NUMBER_OF_BALLS; j++) {

		if (this->balls[j]->fallInside(table)) {
			if (j != BLANC) {
				ballInsideHoleType = this->balls[j]->getType(); //////
				this->balls[j]->setSpeed(Vector(0, 0)); /////
				delete this->balls[j];
				string ballToMoveType = this->balls[numberOfBalls - 1]->getType(); ////
				this->balls[j] = this->balls[numberOfBalls - 1];
				this->balls[j]->setType(ballToMoveType); /////
				numberOfBalls--;
			}
			if (j == BLANC) {
				this->balls[j]->setPosition(Point(this->width / 2, 3 * this->height / 3 - 50.0, true));
				this->balls[j]->setSpeed(Vector(0, 0));
			}
		}
	}
	return ballInsideHoleType;
}



void Game::displayScreen(SDL_Renderer* renderer, int& minIndex, string& ballInsideHoleType)
{
	clearWindow(renderer);
	SDL_Event event = getNextEvent();

	this->displayTable(renderer);
	this->displayBalls(renderer, event);
	this->displayQueues(renderer, event);

	minIndex = this->visualizeBallPath(renderer);
	this->listenForBallCollision();

	ballInsideHoleType = getAndRemoveBallInsideHole(minIndex);

	showRenderingBuffer(renderer);
	//endOfGame = keypressed(event, '\033');
}

void Game::displayScore()
{
	this->players[0]->isTurn()
		? cout << "Player 1 next..." <<
		"P1= " << this->players[0]->getTotalBall() << "(" << players[0]->getPlayerBallsType() << ")" << ", P2= " << this->players[1]->getTotalBall() << "(" << players[1]->getPlayerBallsType() << ")" << endl

		: cout << "Player 2 next..." <<
		"P1= " << this->players[0]->getTotalBall() << "(" << players[0]->getPlayerBallsType() << ")" << ", P2= " << this->players[1]->getTotalBall() << "(" << players[1]->getPlayerBallsType() << ")" << endl;

}

void Game::waitForPlayerHit(SDL_Renderer* renderer, int& minIndex, string& ballInsideHoleType)
{
	this->displayScore();

	if (this->players[0]->isTurn() || this->players[1]->isTurn()) {
		do {
			displayScreen(renderer, minIndex, ballInsideHoleType);
		} while (!this->balls[minIndex]->wasHit);
		cout << "Ball was hit!" << endl;
	}
}

void Game::waitForBallToStop(int& minIndex, SDL_Renderer* renderer, string& ballInsideHoleType)
{
	int ballInMotionIndex = minIndex; //Make a copy of the hit ball index
	bool stopped = false;
	int count = 0;
	do {
		this->displayScreen(renderer, minIndex, ballInsideHoleType);
		count = 0;
		for (int i = 0; i < this->numberOfBalls; i++) {
			if (abs(this->balls[i]->getSpeed().x) <= 3 && abs(this->balls[i]->getSpeed().y) <= 3) {
				count++;
			}
		}
		if (count == this->numberOfBalls) {
			stopped = true;
		}
	} while (stopped == false);
	cout << "All balls have stopped" << endl;
	cout << "========================================================" << endl;
}

bool Game::player1MissesTheHole(std::string& ballInsideHoleType)
{
	return this->players[0]->isTurn() && ballInsideHoleType == "";
}

bool Game::player2MissesTheHole(std::string& ballInsideHoleType)
{
	return this->players[1]->isTurn() && ballInsideHoleType == "";
}

void Game::switchToPlayer2()
{
	this->players[1]->setTurn(true);
	this->players[0]->setTurn(false);
}

void Game::switchToPlayer1()
{
	this->players[0]->setTurn(true);
	this->players[1]->setTurn(false);
}

bool Game::player1InsertedBallRayée(std::string& ballInsideHoleType)
{
	return this->players[0]->isTurn() && ballInsideHoleType == "rayée";
}

bool Game::player1InsertedBallPleine(std::string& ballInsideHoleType)
{
	return this->players[0]->isTurn() && ballInsideHoleType == "pleine";
}

bool Game::player2InsertedBallRayée(std::string& ballInsideHoleType)
{
	return this->players[1]->isTurn() && ballInsideHoleType == "rayée";
}

bool Game::player2InsertedBallPleine(std::string& ballInsideHoleType)
{
	return this->players[1]->isTurn() && ballInsideHoleType == "pleine";
}

void Game::player1GotBallsRayées()
{
	this->players[0]->decrementTotalBall();
	this->players[0]->getQueue()->setColor(BALL_RAYEE);//RED
	this->players[0]->setPlayerBalls("RED");
	this->players[1]->getQueue()->setColor(BALL_PLEINE);//BLUE
	this->players[1]->setPlayerBalls("BLUE");
	this->playersDontHaveSpecificBallType = false;
}

void Game::player1GotBallsPleines()
{
	this->players[0]->decrementTotalBall();
	this->players[0]->getQueue()->setColor(BALL_PLEINE);//BLUE
	this->players[0]->setPlayerBalls("BLUE");
	this->players[1]->getQueue()->setColor(BALL_RAYEE);//RED
	this->players[1]->setPlayerBalls("RED");
	this->playersDontHaveSpecificBallType = false;
}

void Game::player2GotBallsRayées()
{
	this->players[1]->decrementTotalBall();
	this->players[1]->getQueue()->setColor(BALL_RAYEE);//RED
	this->players[1]->setPlayerBalls("RED");
	this->players[0]->getQueue()->setColor(BALL_PLEINE);//BLUE
	this->players[0]->setPlayerBalls("BLUE");
	this->playersDontHaveSpecificBallType = false;
}

void Game::player2GotBallsPleines()
{
	this->players[1]->decrementTotalBall();
	this->players[1]->getQueue()->setColor(BALL_PLEINE);//BLUE
	this->players[1]->setPlayerBalls("BLUE");
	this->players[0]->getQueue()->setColor(BALL_RAYEE);//RED
	this->players[0]->setPlayerBalls("RED");
	this->playersDontHaveSpecificBallType = false;
}

void Game::start() {

	SDL_Renderer* renderer = init_SDL("Billard game");

	//ROUND 1: get ball type
	int minIndex = -1;
	string ballInsideHoleType = "";

	while (playersDontHaveSpecificBallType) {
		this->waitForPlayerHit(renderer, minIndex, ballInsideHoleType);
		this->waitForBallToStop(minIndex, renderer, ballInsideHoleType);

		if (this->player1MissesTheHole(ballInsideHoleType)) {
			this->switchToPlayer2();
		}
		else if (player2MissesTheHole(ballInsideHoleType)) {
			this->switchToPlayer1();
		}


		else if (this->player1InsertedBallRayée(ballInsideHoleType)) {
			this->switchToPlayer1();
			this->player1GotBallsRayées();
		}
		
		else if (this->player1InsertedBallPleine(ballInsideHoleType)) {
			this->switchToPlayer1();
			this->player1GotBallsPleines();
		}

		
		else if (this->player2InsertedBallRayée(ballInsideHoleType)) {
			this->switchToPlayer2();
			this->player2GotBallsRayées();
		}
		
		else if (player2InsertedBallPleine(ballInsideHoleType)) {
			this->switchToPlayer2();
			this->player2GotBallsPleines();
		}
	}

	//ROUND 2: insert
	minIndex = -1;
	ballInsideHoleType = "";
	do {
		cout << "Round 2" << endl;
		this->waitForPlayerHit(renderer, minIndex, ballInsideHoleType);
		this->waitForBallToStop(minIndex, renderer, ballInsideHoleType);

		//TODO:
		if (this->player1MissesTheHole(ballInsideHoleType)) {
			this->switchToPlayer2();
		}
		else if (player2MissesTheHole(ballInsideHoleType)) {
			this->switchToPlayer1();
		}

	} while (this->players[0]->getTotalBall() != 0 || this->players[0]->getTotalBall() != 0);

	//ROUND 3: insert black ball

}