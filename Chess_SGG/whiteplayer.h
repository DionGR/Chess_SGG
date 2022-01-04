#pragma once

#include "player.h"

/**
* WhitePlayer Singleton Class
*
* Restricts the chessboard to 1 instance.
*/
class WhitePlayer : public Player
{
private:
	WhitePlayer(): Player(Color::WHITE) {};
	static WhitePlayer* m_instance;
public:
	static WhitePlayer* getInstance();
	void releaseInstance();
};

