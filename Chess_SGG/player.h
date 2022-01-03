#pragma once

#include "global.h"

#include "immaterial.h"

#include "square.h"
#include "chesspiece.h"

/**
* Player Abstract Class
*
* Handles a player's attributes as well as 
* the movement a player performs on their pieces.
*/
class Player: public Immaterial
{
protected:
	Player(Color color) { m_color = color; };
	Color m_color;

	class Chesspiece* m_active_piece{ nullptr };
public:
	virtual void releaseInstance() = 0;

	bool update(piecelist_t& pieces, Square* squares[5][4]);

	Color getColor() { return m_color; };
};

