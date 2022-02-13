#pragma once

#include "chesspiece.h"

class Pawn: public Chesspiece
{
private:
	void init() override;
public:
	Pawn(Color color);

    bool canOccupy(const Square& square, Square* square_arr[BOARD_HEIGHT][BOARD_WIDTH]) override;
};

