#include "pawn.h"


/* Initializes the chesspiece's colour and basic attributes and calls the init method */
Pawn::Pawn(Color color) :
	Chesspiece{ color, "Pawn" , SQUARE_HEIGHT + 60.f, (color == Color::WHITE) ? SQUARE_HEIGHT - 20.f : CANVAS_HEIGHT - SQUARE_HEIGHT + 20.f}
{
	init();
}


/* Sets the brush's texture according to the colour */
void Pawn::init()
{
	switch (m_color) {
		case(Color::WHITE):
			m_br.texture = W_PAWN_PATH;
			break;
		case(Color::BLACK):
			m_br.texture = B_PAWN_PATH;
			break;
	}
}


/* Checks whether the piece can occupy the square given */
bool Pawn::canOccupy(const Square& square, Square* square_arr[BOARD_HEIGHT][BOARD_WIDTH])
{
	int srcI{ m_square->getIndexI() };
	int srcJ{ m_square->getIndexJ() };
	int dstI{ square.getIndexI() };
	int dstJ{ square.getIndexJ() };

	int di{ m_color == Color::WHITE ? 1 : -1 };					// I-index is negative when moving as a BLACK pawn

	if (dstI - srcI == di && srcJ == dstJ)						// If the move is one step forward vertically (I-axis)
		return square.isEmpty();								// Can occupy if the square is empty
	else if (dstI - srcI == di && std::abs(dstJ - srcJ) == 1)	// If the move is one step diagonally
		return square.hasEnemyOf(*this);						// Can occupy if the square is occupied by an enemy
	else if (dstI - srcI == di * 2 && srcJ == dstJ && !m_moved){// If the move is two steps and we haven't moved
		/* Can occupy if it's the second step from the start and there are no obstacles */
		return square.isEmpty() && square_arr[srcI + di][dstJ]->isEmpty();				
	}

	return false;												// Else the move is invalid
}