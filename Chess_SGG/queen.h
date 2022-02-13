#pragma once

#include "chesspiece.h"

class Queen: public Chesspiece
{
private:
	void init() override;
public:
	Queen(Color color);

	bool canOccupy(const Square& square, Square* square_arr[BOARD_HEIGHT][BOARD_WIDTH]) override;
};

