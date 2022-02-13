#pragma once

#include "chesspiece.h"

class Knight: public Chesspiece
{
private:
	void init() override;
public:
	Knight(Color color);

	bool canOccupy(const Square& square, Square* square_arr[BOARD_HEIGHT][BOARD_WIDTH]) override;
};

