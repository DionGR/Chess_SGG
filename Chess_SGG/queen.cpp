#include "queen.h"


/* Initializes the chesspiece's colour and basic attributes and calls the init method */
Queen::Queen(Color color) :
	Chesspiece{ color, "Queen", SQUARE_HEIGHT + 315.f,  (color == Color::WHITE) ? SQUARE_HEIGHT - 20.f : CANVAS_HEIGHT - SQUARE_HEIGHT + 20.f }
{
	init();
}


/* Sets the brush's texture according to the colour */
void Queen::init()
{
	switch (m_color) {
		case(Color::WHITE):
			m_br.texture = W_QUEEN_PATH;
			break;
		case(Color::BLACK):
			m_br.texture = B_QUEEN_PATH;
			break;
	}
}


/* Checks whether the piece can occupy the square given */
bool Queen::canOccupy(const Square& square, Square* square_arr[BOARD_HEIGHT][BOARD_WIDTH])
{
	int srcI{ m_square->getIndexI() };
	int srcJ{ m_square->getIndexJ() };
	int dstI{ square.getIndexI() };
	int dstJ{ square.getIndexJ() };

	int di{ (srcI < dstI) ? 1 : -1 };
	int dj{ (srcJ < dstJ) ? 1 : -1 };

	if (srcI == dstI) {													// If it is vertical or horizontal and there are no obstacles
		for (int j{ srcJ + dj }; j != dstJ; j += dj){					// It is valid, similar to Rook
			if (square_arr[srcI][j]->getPiece() != nullptr)
				return false;
		}
		return 	square.hasEnemyOf(*this) || square.isEmpty();			// It is valid if it has an enemy
	}
	else if (srcJ == dstJ) {											
		for (int i{ srcI + di }; i != dstI; i += di) {
			if (square_arr[i][srcJ]->getPiece() != nullptr)
				return false;
		}
		return 	square.hasEnemyOf(*this) || square.isEmpty();
	}else if (std::abs(dstI - srcI) == std::abs(dstJ - srcJ)) {			// If the move is diagonal 
		for (int i{ 1 }; i < std::abs(srcI - dstI); ++i) {				// Same as Bishop
			if (square_arr[srcI + i * di][srcJ + i * dj]->getPiece() != nullptr)
				return false;
		}
		return 	square.hasEnemyOf(*this) || square.isEmpty();			
	}

	return false;														// Any other case, invalid
}