#pragma once

#include "immaterial.h"

#include "square.h"

#include "chesspiece.h"
#include "king.h"
#include "rook.h"

/**
* Player Abstract Class
*
* Handles a player's attributes as well as 
* the movement a player performs on their pieces.
*/
class Player: public Immaterial
{
protected:
	Player(Color color);
	const Color m_color;

	class Chesspiece* m_active_piece;
public:
	virtual void releaseInstance() = 0;

	bool update(const piecelist_t& pieces, Square* squares[BOARD_WIDTH][BOARD_HEIGHT]);

	Color getColor() const;
};

