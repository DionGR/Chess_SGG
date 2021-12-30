#pragma once

#include "global.h"

#include <deque>
#include "square.h"
#include "chesspiece.h"




class Player: GameObject
{
protected:
	Color m_color;
	Player(Color color) { m_color = color; };

	class Chesspiece* m_active_piece = nullptr;
public:
	Color getColor() { return m_color; };
	virtual void init() {};
	virtual void draw() {};
	bool update(piecelist_t& pieces, Square* squares[5][4]);

	virtual void releaseInstance() {};
};

