#include "pawn.h"


/* Initializes the chesspiece's colour and basic attributes and calls the init method */
Pawn::Pawn(Color color) :
	Chesspiece(color)
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
bool Pawn::canOccupy(Square* square, Square* square_arr[5][4])
{
	int srcI = m_square->getIndexI();
	int srcJ = m_square->getIndexJ();
	int dstI = square->getIndexI();
	int dstJ = square->getIndexJ();

	int di{ m_color == Color::WHITE ? 1 : -1 };					// I-index is negative when moving as a BLACK pawn

	if (dstI - srcI == di && srcJ == dstJ)						// If the move is one step forward vertically (I-axis)
		return !square_arr[dstI][dstJ]->getPiece();				// Can occupy if the square is empty
	else if (dstI - srcI == di && std::abs(dstJ - srcJ) == 1)	// If the move is one step diagonally
		return !!square_arr[dstI][dstJ]->getPiece();			// Can occupy if the square is occupied by an enemy
	
	return false;												// Else the move is invalid
}