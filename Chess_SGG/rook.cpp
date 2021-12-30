#include "rook.h"


/* Initializes the chesspiece's colour and basic attributes and calls the init method */
Rook::Rook(Color color) :
	Chesspiece(color)
{
	init();
}


/* Sets the Rookbrush's texture according to the colour */
void Rook::init()
{
	switch (m_color) {
		case(Color::WHITE):
			m_br.texture = W_TOWER_PATH;
			break;
		case(Color::BLACK):
			m_br.texture = B_TOWER_PATH;
			break;
	}
}


/* Checks whether the piece can occupy the square given */
bool Rook::canOccupy(Square* square, Square* square_arr[5][4])
{
	int srcI = m_square->getIndexI();
	int srcJ = m_square->getIndexJ();
	int dstI = square->getIndexI();
	int dstJ = square->getIndexJ();

	if (srcI != dstI && srcJ != dstJ) return false;				// If the move isn't exactly vertical or horizontal, it is invalid

	if (srcI == dstI) {											// If it is vertical
		int di{ (srcJ < dstJ) ? 1 : -1 };						// 1 if the move was upwards, -1 if downwards
					
		for (int j{ srcJ + di }; j != dstJ; j += di)			// And there are no pieces in the way
			if (square_arr[srcI][j]->getPiece() != nullptr)
				return false;									
	}
	else if (srcJ == dstJ) {									// If it is horizontal
		int dj{ (srcI < dstI) ? 1 : -1 };	
			
		for (int i{ srcI + dj }; i != dstI; i += dj)			// And there are no pieces in the way
			if (square_arr[i][srcJ]->getPiece() != nullptr)
				return false;
	}

	return true;												// The move is valid
}