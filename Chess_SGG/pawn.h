#pragma once

#include "chesspiece.h"

class Pawn: public Chesspiece
{
private:
	void init();
public:
	Pawn(Color color);

    bool canOccupy(Square* square, Square* square_arr[5][4]);
};

