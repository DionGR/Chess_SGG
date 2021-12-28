#pragma once

#include "player.h"

class WhitePlayer : public Player
{
private:
	WhitePlayer() : Player(Color::WHITE) {};
	static WhitePlayer* m_instance;
public:
	static WhitePlayer* getInstance();
	void releaseInstance();

	void init();
	void draw();

};

