#pragma once

#include "global.h"

class Menu
{
private:
	Menu(){};
	static Menu* m_instance;

public:
	static Menu* getInstance();
	void releaseInstance();

	void init();
	void draw();
	void update();
};

