#pragma once

void findNearestBallIndex(Ball* ball[2], Queue& queue);

void displayTrou(Table* trouBillard[6]);

void displayQueue(Queue& queue, SDL_Renderer* renderer, const Color& queueColor, SDL_Event& event);

void displayTable(Table& table, SDL_Renderer* renderer);

void listenForBallCollision(int numberOfBalls, Ball* balls[15]);

void removeBallInsideHole(int& numberOfBalls, Ball* balls[15], const Table& table);

void visualizeBallPath(Ball* balls[15], Queue& queue, int numberOfBalls, SDL_Renderer* renderer);

void removeBallIfInsideHole(int& numberOfBalls, Ball* balls[15], Table* trousBillard[6]);

void displayTrous(Table* trousBillard[6], SDL_Renderer* renderer, SDL_Event& event);

void displayBalls(int nombreLigne, int numberOfBalls, Ball* balls[15], SDL_Renderer* renderer, const Color& ballColor2, SDL_Event& event, Queue& queue);
