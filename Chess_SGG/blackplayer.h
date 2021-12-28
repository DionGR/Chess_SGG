#pragma once

#include "player.h"



class BlackPlayer: public Player
{
private:
	BlackPlayer(): Player(Color::BLACK) {};
	static BlackPlayer* m_instance;
public:
	static BlackPlayer* getInstance();
	void releaseInstance();

	void init();
	void draw();
};

