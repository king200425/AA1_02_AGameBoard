#pragma once
#include "Types.h"

//Inicializa el tablero (como paredes, pinchos, gamas y jugador)
void initializeBoadr(BoardCell**& board, int rows, int cols, Player& player);

//Verifica si el movimiento es valido(no sale del mapa y pared)
bool checkMovement(const Position& pos, PlayerMovement move, BoardCell** board, int rows, int cols);

//Actualiza el score del jugador sumando
void addScore(Player& player);

//Actualiza la posicion del jugador
void setPosition(Player& player, const Position& newPos);

//Devuelve true si hay una gema en la siguiente casilla
bool existGem(const Position& playerPos, PlayerMovement move, BoardCell** board);

//
void movePlayer(Player& player, PlayerMovement move, BoardCell** board);

bool gameOver(BoardCell** board, int rows, int cols, bool isSpikeStepped);

void printBoard(BoardCell** board, int rows, int cols);

void destroyBoard(BoardCell**& board, int rows);