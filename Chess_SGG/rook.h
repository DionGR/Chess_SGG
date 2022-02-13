#pragma once

#include "chesspiece.h"

class Rook: public Chesspiece
{
private:
	void init() override;
public:
	Rook(Color color);

	bool canOccupy(const Square& square, Square* square_arr[BOARD_HEIGHT][BOARD_WIDTH]) override;
};

