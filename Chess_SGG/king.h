#pragma once

#include "chesspiece.h"
#include "rook.h"

class King: public Chesspiece
{
private:
	void init() override;
public:
	King(Color color);

	bool canOccupy(const Square& square, Square* square_arr[BOARD_HEIGHT][BOARD_WIDTH]) override;
	bool isThreatened(const piecelist_t& enemies, Square* square_arr[BOARD_HEIGHT][BOARD_WIDTH]);
};

