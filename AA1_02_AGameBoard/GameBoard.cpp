#include<iostream>
#include"GameBoard.h"
#include<cstdlib>

//Inicializa el tablero
void initializeBoard(BoardCell**& board, int rows, int cols, Player& player) {

	board = new BoardCell * [rows];
	for (int i = 0; i < rows; ++i) {
		board[i] = new BoardCell[cols];
	}

	// Llenar el tablero: Bordes son paredes, el resto está vacío
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1) {
				board[i][j] = BoardCell::WALL;
			}
			else {
				board[i][j] = BoardCell::EMPTY;
			}
		}
	}

	//Calcular cantidades máximas
	int playebleCells = (rows - 2) * (cols - 2);
	int maxSpikes = static_cast<int>(playebleCells * 0.10f);
	int maxGems = static_cast<int>(playableCells * 0.25f);

	// Colocar pinchos aleatoriamente
	int spikesPlaced = 0;
	while (spikesPlaced < maxSpikes) {
		int r = (std::rand() % (rows - 2)) + 1;
		int c = (std::rand() % (cols - 2)) + 1;
		if (board[r][c] == BoardCell::EMPTY) {
			board[r][c] = BoardCell::SPIKE;
			spikesPlaced++;
		}
	}

	//Colocar gemas aleatoriamente
	int gemsPlaced = 0;
	while (gemsPlaced < maxGems) {
		int r = (std::rand() % (rows - 2)) + 1;
		int c = (std::rand() % (cols - 2)) + 1;
		if (board[r][c] == BoardCell::EMPTY) {
			board[r][c] = BoardCell::GEM;
			gemsPlaced++;
		}
	}

	//Colocar al jugador en una posición aleatorio
	int pr = (std::rand() % (rows - 2)) + 1;
	int pc = (std::rand() % (cols - 2)) + 1;
	player.pos.row = pr;
	player.pos.col = pc;
	board[pr][pc] = BoardCell::PLAYER;

}

//Verifica si el movimiento es válido
bool checkMovement(const Position& pos, PlayerMovement move, BoardCell** board, int rows, int cols) {
	int nextRow = pos.row;
	int nextCol = pos.col;

	switch (move) {
		case PlayerMovement::UP:    nextRow--; break;
		case PlayerMovement::DOWN:  nextRow++; break;
		case PlayerMovement::LEFT:  nextCol--; break;
		case PlayerMovement::RIGHT: nextCol++; break;
	}

	// Evitar salir de los límites
	if (nextRow < 0 || nextRow >= rows || nextCol < 0 || nextCol >= cols) return false;
	if (board[nextRow][nextCol] == BoardCell::WALL) return false;

	return true;
}

//Añadir score
void addScore(Player& player) {
	player.score += 1;
}

//Actualizar posición
void setPosition(Player& player, const Position& newPos) {
	player.pos = newPos;
}

//Verificar si hay gema en el siguiente movimiento

bool existGem(const Position& playerPos, PlayerMovement move, BoardCell** board) {
	int nextRow = playerPos.row;
	int nextCol = playerPos.col;

	switch (move) {
		case PlayerMovement::UP:    nextRow--; break;
		case PlayerMovement::DOWN:  nextRow++; break;
		case PlayerMovement::LEFT:  nextCol--; break;
		case PlayerMovement::RIGHT: nextCol++; break;
	}

	return board[nextRow][nextCol] == BoardCell::GEM;
}

//Mover jugador en el tablero
void movePlayer(Player& player, PlayerMovement move, BoardCell** board) {
	// Vaciar la casilla actual
	board[player.pos.row][player.pos.col] = BoardCell::EMPTY;

	// Actualizar coordenadas
	switch (move) {
	case PlayerMovement::UP:    player.pos.row--; break;
	case PlayerMovement::DOWN:  player.pos.row++; break;
	case PlayerMovement::LEFT:  player.pos.col--; break;
	case PlayerMovement::RIGHT: player.pos.col++; break;
	}

	// El jugador se dibuja en su nueva posición
	board[player.pos.row][player.pos.col] = BoardCell::PLAYER;
}

//Condición de Game Over (gana si 0 gemas, pierde si pisa pincho)
bool gameOver(BoardCell** board, int rows, int cols, bool isSpikeStepped) {
	if (isSpikeStepped) {
		std::cout << "\n>>> HAS PISADO UN PINCHO! GAME OVER <<<\n";
		return true;
	}

	// Contar si quedan gemas
	int gemCount = 0;
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			if (board[i][j] == BoardCell::GEM) {
				gemCount++;
			}
		}
	}

	if (gemCount == 0) {
		std::cout << "\n>>> ¡HAS RECOGIDO TODAS LAS GEMAS! ¡GANASTE! <<<\n";
		return true;
	}

	return false;
}

//Imprimir tablero
void printBoard(BoardCell** board, int rows, int cols) {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			switch (board[i][j]) {
			case BoardCell::WALL:   std::cout << " # "; break;
			case BoardCell::EMPTY:  std::cout << " . "; break;
			case BoardCell::SPIKE:  std::cout << " ^ "; break;
			case BoardCell::GEM:    std::cout << " $ "; break;
			case BoardCell::PLAYER: std::cout << " P "; break;
			}
		}
		std::cout << "\n";
	}
}

//Destruir tablero y liberar memoria
void destroyBoard(BoardCell**& board, int rows) {
	if (board != nullptr) {
		for (int i = 0; i < rows; ++i) {
			delete[] board[i];
		}
		delete[] board;
		board = nullptr;
	}
}