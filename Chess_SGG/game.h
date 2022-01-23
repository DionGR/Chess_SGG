#pragma once

#include "soundhandler.h"

#include "chessboard.h"

/**
* Game Singleton Class
*
* Responsible for keeping track of the game state
* and the final menus.
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
	~Game();
	static Game* getInstance();
	void releaseInstance();

	void init();
	void draw();
	void update();
};

