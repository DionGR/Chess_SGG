#pragma once

#include "gameobject.h"
#include "chesspiece.h"
#include "pawn.h"
#include "king.h"
#include "queen.h"
#include "rook.h"
#include "square.h"

#include "player.h"
#include "blackplayer.h"
#include "whiteplayer.h"

#include <deque>


class Chessboard: GameObject
{
public:
	enum class State { INIT, LOADING, PLAYING };
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



