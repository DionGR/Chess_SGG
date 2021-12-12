#pragma once

#include "player.h"

class Game{
	Player * player = nullptr;

public:
	Game();
	~Game();
	void update();
	void draw();
	void init();
};

