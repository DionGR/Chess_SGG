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


using capturemap_t = std::unordered_map<std::string, std::pair<int, cords>>;

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
	graphics::Brush m_text_br;

	class Player* m_white;
	class Player* m_black;
	class Player** m_active_player;

	class Square* m_squares[BOARD_WIDTH][BOARD_HEIGHT];
	piecelist_t m_w_pieces;
	piecelist_t m_b_pieces;
	capturemap_t m_captured;

	unsigned m_turns{};

	/* Static for multithreading practice purposes */
	static void generateBoard(Square* squares[BOARD_HEIGHT][BOARD_WIDTH]);
	static void generatePieces(Color color, piecelist_t& piecelist);
	static void assignPieces(piecelist_t& w_pieces, piecelist_t& b_pieces, Square* squares[BOARD_HEIGHT][BOARD_WIDTH]);
	static void initCaptured(piecelist_t& pieces, capturemap_t& captured);
public:
	~Chessboard();
	static Chessboard* getInstance();
	void releaseInstance();

	Player& getActivePlayer() const;	// Must be non-null for our purpose, therefore we return reference. 

	void init() override;
	void draw() override;
	void update(State& state);
};
