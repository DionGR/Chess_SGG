#pragma once

#include "global.h"

#include <deque>
#include "square.h"
#include "chesspiece.h"

using squarelist_t = std::deque<Square*>;
using squarelist_itr_t = std::deque<Square*>::iterator;
using squarelist_rvitr_t = std::deque<Square*>::reverse_iterator;

using piecelist_t = std::deque<Chesspiece*>;
using piecelist_itr_t = std::deque<Chesspiece*>::iterator;
using piecelist_rvitr_t = std::deque<Chesspiece*>::reverse_iterator;


class Player
{
protected:
	Color m_color;
	Player(Color color) { m_color = color; };
	Chesspiece* m_active_piece = nullptr;
public:
	Color getColor() { return m_color; };
	virtual void init() {};
	virtual void draw() {};
	void update(piecelist_t& pieces, Square* squares[5][4]);
	virtual void releaseInstance() {};
};

