#pragma once

#include "gameobject.h"

class Player: public GameObject{
	Player();
	~Player();
	void update() override;
	void draw() override;
	void init() override;
};

