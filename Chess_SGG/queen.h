#pragma once

#include "chesspiece.h"

class Queen: public Chesspiece
{
private:
	void init();
public:
	Queen(Color color);

	bool canOccupy(Square* square, Square* square_arr[BOARD_HEIGHT][BOARD_WIDTH]);
};

