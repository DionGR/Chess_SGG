#pragma once

#include "global.h"

/**
* Abstract GameObject interface
* 
* Will provide a model for creating and designing objects in our game.
*/
class GameObject {
public:
	virtual ~GameObject() {};
	virtual void draw() {};
	virtual void init() {};
	virtual void update() {};
};

