#pragma once

#include "global.h"

/**
* Abstract GameObject interface
* 
* Will provide a model for creating and designing objects in our game.
*/
class GameObject {
public:
	virtual void init() = 0;
	virtual void draw() = 0;
	virtual void update() {};
};

