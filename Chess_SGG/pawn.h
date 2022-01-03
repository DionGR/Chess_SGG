#pragma once

#include "chesspiece.h"

class Pawn: public Chesspiece
{
private:
	void init();
public:
	Pawn(Color color);

    bool canOccupy(Square* square, Square* square_arr[BOARD_HEIGHT][BOARD_WIDTH]);
};

