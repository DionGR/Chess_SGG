#pragma once

#include "soundhandler.h"

#include "chessboard.h"

/**
* Game Singleton Class
*
* Is responsible for keeping track of the game status,
* from the beggining to handling 
*/
class Game
{
private:
	Game() {};
	static Game* m_instance;

	graphics::Brush m_text_br;

	State m_state = State::INIT;

	Chessboard* m_board{};
public:
	static Game* getInstance();
	void releaseInstance();

	void init();
	void draw();
	void update();
};

