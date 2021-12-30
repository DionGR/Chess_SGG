#pragma once

/** 
* Material Abstract Class
* 
* Used by all objects that can be seen on the player's screen, material objects.
*/
class Material {
protected:
	Material() {}
	Material(float x_pos, float y_pos) : m_pos{ x_pos, y_pos } {}
	float m_pos[2]{};
public:
	virtual void setPosX(float x) {};
	virtual void setPosY(float x) {};
	float getPosX() const { return m_pos[0]; }
	float getPosY() const { return m_pos[1]; }

	/* Checks whether the piece contains certain coordinates, for collision purposes */
	bool contains(float x, float y) const { return distance(x, y, m_pos[0], m_pos[1]) < 25.0f; }
};
