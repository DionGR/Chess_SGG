#include "bishop.h"


/* Initializes the chesspiece's colour and basic attributes and calls the init method */
Bishop::Bishop(Color color) :
	Chesspiece{ color, "Bishop", SQUARE_HEIGHT + 195.f, (color == Color::WHITE) ? SQUARE_HEIGHT - 20.f : CANVAS_HEIGHT - SQUARE_HEIGHT + 20.f }
{
	init();
}


/* Sets the brush's texture according to the colour */
void Bishop::init()
{
	switch (m_color) {
	case(Color::WHITE):
		m_br.texture = W_BISHOP_PATH;
		break;
	case(Color::BLACK):
		m_br.texture = B_BISHOP_PATH;
		break;
	}
}


/* Checks whether the piece can occupy the square given */
bool Bishop::canOccupy(const Square& square, Square* square_arr[BOARD_HEIGHT][BOARD_WIDTH])
{
	int srcI{ m_square->getIndexI() };
	int srcJ{ m_square->getIndexJ() };
	int dstI{ square.getIndexI() };
	int dstJ{ square.getIndexJ() };

	int di{ (srcI < dstI) ? 1 : -1 };
	int dj{ (srcJ < dstJ) ? 1 : -1 };

	if (std::abs(dstI - srcI) == std::abs(dstJ - srcJ)) {							// If the move is diagonal 
		for (int i{ 1 }; i < std::abs(srcI - dstI); ++i) {							// And there are no objects
			if (square_arr[srcI + i * di][srcJ + i * dj]->getPiece() != nullptr)
				return false;
		}
		return 	square.hasEnemyOf(*this) || square.isEmpty();						// It is valid if it has an enemy
	}
	
	return false;
}