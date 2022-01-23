#pragma once

#include "player.h"

/**
* BlackPlayer Singleton Class
*
* Restricts the chessboard to 1 instance.
*/
class BlackPlayer: public Player
{
private:
	BlackPlayer(): Player(Color::BLACK) {};
	static BlackPlayer* m_instance;
public:
	static BlackPlayer* getInstance();
	void releaseInstance();
};
