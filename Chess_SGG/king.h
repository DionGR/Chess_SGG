#pragma once

#include "chesspiece.h"

class King: public Chesspiece
{
private:
	void init();
public:
	King(Color color);

	bool canOccupy(Square* square, Square* square_arr[BOARD_HEIGHT][BOARD_WIDTH]);
};

