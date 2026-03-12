#pragma once

//Control de Jugador
enum class PlayerMovement {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

//Mapa
enum class BoardCell {
	EMPTY,
	WALL,
	SPIKE,
	GEM,
};

//Ubicacion
struct Position {
	int row = 0;
	int col = 0;
};

struct Player {
	Position pos;   //Ubicacion actual del jugador
	int score = 0;
};