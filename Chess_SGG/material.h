#pragma once

#include "gameobject.h"

/** 
* Material "Abstract" Class
* 
* Used by all GameObjects that can be seen on the canvas.
* Forced abstraction by making constructor protected.
*/
class Material: public GameObject 
{
protected:
	Material() {};
	Material(Color color, float x_pos, float y_pos, float width, float height) : m_color(color), m_pos{ x_pos, y_pos }, m_size{ width, height } { m_br.outline_opacity = 0.0f; }

	Color m_color{};
	graphics::Brush m_br;

	cords m_pos{};
	const float m_size[2]{};
public:
	void draw() override { graphics::drawRect(m_pos.x_pos, m_pos.y_pos, m_size[0], m_size[1], m_br); }

	[[Obsolete("Object does not need updating. Inherited from GameObject, no usage.", true)]]
	void update() override {}

	virtual void setPosX(float x) {};
	virtual void setPosY(float x) {};
	float getPosX() const { return m_pos.x_pos; }
	float getPosY() const { return m_pos.y_pos; }
	Color getColor() const { return m_color; };

	/* Checks whether the piece contains certain coordinates, for collision purposes */
	bool contains(float x, float y) const { return distance(x, y, m_pos.x_pos, m_pos.y_pos) < SQUARE_HEIGHT/2.0f; }
};
