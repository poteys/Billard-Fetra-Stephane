#include <iostream>
#include <time.h>
#include <SDL.h>
#include "Game.h"
using namespace std;

constexpr auto WIDTH = 400, HEIGHT = 800;

int main(int argc, char** argv) {

	Game billardGame(WIDTH,HEIGHT);
	
	billardGame.start();
	return 0;
}