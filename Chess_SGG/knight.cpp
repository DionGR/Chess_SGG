#include "knight.h"


/* Initializes the chesspiece's colour and basic attributes and calls the init method */
Knight::Knight(Color color) :
	Chesspiece{ color, "Knight", SQUARE_HEIGHT + 235.f, (color == Color::WHITE) ? SQUARE_HEIGHT - 20.f : CANVAS_HEIGHT - SQUARE_HEIGHT + 20.f }
{
	init();
}


/* Sets the brush's texture according to the colour */
void Knight::init()
{
	switch (m_color) {
	case(Color::WHITE):
		m_br.texture = W_KNIGHT_PATH;
		break;
	case(Color::BLACK):
		m_br.texture = B_KNIGHT_PATH;
		break;
	}
}


/* Checks whether the piece can occupy the square given */
bool Knight::canOccupy(const Square& square, Square* square_arr[BOARD_HEIGHT][BOARD_WIDTH])
{
	int srcI{ m_square->getIndexI() };
	int srcJ{ m_square->getIndexJ() };
	int dstI{ square.getIndexI() };
	int dstJ{ square.getIndexJ() };

	int di{ (srcI < dstI) ? 1 : -1 };
	int dj{ (srcJ < dstJ) ? 1 : -1 };

	/* Two steps diagonally/vertically and one step up/down or vice versa */
	if ((dstI - srcI == di && std::abs(dstJ - srcJ) == 2) || (dstJ - srcJ == dj && std::abs(dstI - srcI) == 2)) 						
		return 	square.hasEnemyOf(*this) || square.isEmpty();						
	
	return false;
}