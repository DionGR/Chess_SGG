#pragma once

#include "global.h"

#include "soundhandler.h"

/**
* Menu Singleton Class 
*
* Handles the Main Menu screen and calls the Game Class when 
* the player picks a difficulty.
* Utilizes the Singleton Design Pattern.
*/
class Menu
{
private:
	Menu() {};
	static Menu* m_instance;

	graphics::Brush m_text_br;
public:
	static Menu* getInstance();
	void releaseInstance();

	void init();
	void draw();
	void update();
};

