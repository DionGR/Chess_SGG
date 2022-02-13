#pragma once

#include "chesspiece.h"

class Bishop: public Chesspiece
{
private:
	void init() override;
public:
	Bishop(Color color);

	bool canOccupy(const Square& square, Square* square_arr[BOARD_HEIGHT][BOARD_WIDTH]) override;
};


