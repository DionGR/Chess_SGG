#pragma once

#include "gameobject.h"
#include "material.h"

#include "chesspiece.h"
#include "square.h"
#include "queen.h"
#include "pawn.h"
#include "king.h"
#include "rook.h"

#include "player.h"
#include "blackplayer.h"
#include "whiteplayer.h"

#include "soundhandler.h"

/**
* Chessboard Singleton Class
*
* Responsible for handling all the GameObjects,
* handler of the PLAYING game state.
*/
class Chessboard: public GameObject
{
private:
	Chessboard(){}; 
	static Chessboard* m_instance;

	Player* m_white{};
	Player* m_black{};
	Player** m_active_player{};

	Square* m_squares[5][4]{};
	piecelist_t m_w_pieces;
	piecelist_t m_b_pieces;

	graphics::Brush m_text_br;

	unsigned m_turns{};
public:
	static Chessboard* getInstance();
	void releaseInstance();

	void init();
	void draw();
	void update(State& state);
};



