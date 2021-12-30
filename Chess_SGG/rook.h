#pragma once

#include "chesspiece.h"

class Rook: public Chesspiece
{
private:
	void init();
public:
	Rook(Color color);

	bool canOccupy(Square* square, Square* square_arr[5][4]);
};

