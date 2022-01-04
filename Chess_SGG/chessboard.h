#pragma once

#include "soundhandler.h"

#include "gameobject.h"

#include "blackplayer.h"
#include "whiteplayer.h"

#include "square.h"

#include "bishop.h"
#include "knight.h"
#include "queen.h"
#include "pawn.h"
#include "king.h"
#include "rook.h"



/**
* Chessboard Singleton Class
*
* Responsible for handling all the GameObjects,
* handler of the PLAYING game state.
*/
class Chessboard: public GameObject
{
private:
	Chessboard(); 
	static Chessboard* m_instance;

	Player* m_white;
	Player* m_black;
	Player** m_active_player;

	Square* m_squares[BOARD_WIDTH][BOARD_HEIGHT];
	piecelist_t m_w_pieces;
	piecelist_t m_b_pieces;

	graphics::Brush m_text_br;

	unsigned m_turns{};
public:
	static Chessboard* getInstance();
	void releaseInstance();

	void init() override;
	void draw() override;
	void update(State& state);
};



