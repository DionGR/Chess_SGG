#pragma once

#include "blackplayer.h"
#include "whiteplayer.h"
#include "chessboard.h"
#include "chesspiece.h"


class Game{
public:
	enum class State {
		INIT,
		LOADING,
		IDLE,
		MOVING,
		ATTACKING
	};
private:
	static Game* m_instance;
	State m_state = State::INIT;

	Chessboard* m_board;


	Game() {};
public:
	static Game* getInstance();
	void releaseInstance();

	void init();
	void draw();
	void update();
};

