#pragma once

#include <string>

#include "global.h"

/**
* Abstract GameObject class
* 
* Will provide a model for creating and designing objects in our game.
*/
class GameObject {
public:
	virtual ~GameObject() {};
	virtual void update() {};
	virtual void draw() {};
	virtual void init() {};
};

