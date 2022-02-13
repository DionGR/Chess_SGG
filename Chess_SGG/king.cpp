#include "king.h"


/* Initializes the chesspiece's colour and basic attributes and calls the init method */
King::King(Color color) :
	Chesspiece{ color, "King", SQUARE_HEIGHT + 345.f, (color == Color::WHITE) ? SQUARE_HEIGHT - 20.f : CANVAS_HEIGHT - SQUARE_HEIGHT + 20.f }
{
	init();
}


/* Sets the brush's texture according to the colour */
void King::init()
{
	switch (m_color) {
		case(Color::WHITE):
			m_br.texture = W_KING_PATH;
			break;
		case(Color::BLACK):
			m_br.texture = B_KING_PATH;
			break;
	}
}


/* Checks whether the piece can occupy the square given */
bool King::canOccupy(const Square& square, Square* square_arr[BOARD_HEIGHT][BOARD_WIDTH])
{
	int srcI{ m_square->getIndexI() };
	int srcJ{ m_square->getIndexJ() };
	int dstI{ square.getIndexI() };
	int dstJ{ square.getIndexJ() };

	// The move is valid if it is exactly one step in any direction
	if ((std::abs(dstI - srcI) == 1 && std::abs(dstJ - srcJ) == 1) || (std::abs(dstI - srcI) == 1 && srcJ == dstJ) || (std::abs(dstJ - srcJ) == 1 && srcI == dstI))
		return 	square.hasEnemyOf(*this) || square.isEmpty();

	return false;
}

bool King::isThreatened(const piecelist_t& enemies, Square* square_arr[BOARD_HEIGHT][BOARD_WIDTH]) {
	for (auto const& enemy: enemies) 
		if (enemy->canOccupy(*m_square, square_arr))
			return true;
	return false;
}

