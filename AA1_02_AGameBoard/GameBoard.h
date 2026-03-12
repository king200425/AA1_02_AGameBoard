#pragma once
#include "Types.h"

void initializaBoadr(BoardCell**& board, int rows, int cols, Player& player);

bool checkMovement(const Position& pos, PlayerMovement move, BoardCell** board, int rows, int cols);

void addScore(Player& player);

void setPosition(Player& player, const Position& newPos);

bool existGem(const Position& playerPos, PlayerMovement move, BoardCell** board);

void movePlayer(Player& player, PlayerMovement move, BoardCell** board);

bool gameOver(BoardCell** board, int rows, int cols, bool isSpikeStepped);


void printBoard(BoardCell** board, int rows, int cols);

void destroyBoard(BoardCell**& board, int rows);