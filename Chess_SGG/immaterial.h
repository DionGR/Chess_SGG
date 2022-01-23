#pragma once

#include "gameobject.h"

/**
* Immaterial "Abstract" Class
*
* Used by all GameObjects that cannot be seen on the canvas.
* Forced abstraction by making constructor protected.
*/
class Immaterial : public GameObject 
{
protected:
	Immaterial() {};
public:
	virtual void init() {};
	virtual void update() {};

	[[Obsolete("Immaterial Object does not need drawing. Inherited from GameObject, no usage.", true)]]
	virtual void draw() final {};
};