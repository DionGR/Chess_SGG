#pragma once

#include "chesspiece.h"

class Queen: public Chesspiece
{
private:
	void init();
public:
	Queen(Color color);

	bool canOccupy(Square* square, Square* square_arr[5][4]);
};

