#pragma once

#include "chesspiece.h"
#include "pawn.h"
#include "king.h"
#include "queen.h"
#include "tower.h"

#include "player.h"
#include "blackplayer.h"
#include "whiteplayer.h"

#include "square.h"

#include <deque>

using squarelist_t = std::deque<Square*>;
using squarelist_itr_t = std::deque<Square*>::iterator;
using squarelist_rvitr_t = std::deque<Square*>::reverse_iterator;

using piecelist_t = std::deque<Chesspiece*>;
using piecelist_itr_t = std::deque<Chesspiece*>::iterator;
using piecelist_rvitr_t = std::deque<Chesspiece*>::reverse_iterator;


class Chessboard: GameObject
{
private:
	Chessboard(){}; 
	static Chessboard* m_instance;

	Player* m_white;
	Player* m_black;
	Player** m_active_player;

	Square* m_squares[5][4];
	piecelist_t m_w_pieces;
	piecelist_t m_b_pieces;

	unsigned m_turns{};
public:
	static Chessboard* getInstance();
	void releaseInstance();

	void init();
	void draw();
	void update();
};



