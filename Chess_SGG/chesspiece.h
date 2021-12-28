#pragma once

#include "gameobject.h"
#include "square.h"


class Chesspiece : GameObject {
protected:
	graphics::Brush m_br;

	float m_pos[2]{ 0.0f, 0.0f };
	Color m_color;

	class Square* m_square{ nullptr };

	bool m_highlighted{ false };

	Chesspiece(Color color) : m_color(color) {}
	virtual void init() {};
public:
	bool m_moved{ false };
	virtual void draw() {};
	virtual void update() {};

	void setHighlight(bool state) { m_highlighted = state; }
	void setPosX(float x) { m_pos[0] = x; }
	void setPosY(float x) { m_pos[1] = x; }
	float getPosX() { return m_pos[0]; }
	float getPosY() { return m_pos[1]; }
	bool contains(float x, float y) { return distance(x, y, m_pos[0], m_pos[1]) < 25.0f; };

	Color getColor() { return m_color; }

	Square* getSquare() { return m_square; }
	void setSquare(Square* square) {
		m_square = square; 
	}

};