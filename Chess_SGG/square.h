#pragma once

#include "gameobject.h"
#include "chesspiece.h"

class Square: GameObject
{
protected:
	const float m_pos[2];

	class  Chesspiece* m_occupant;

	graphics::Brush m_br;
public:
	Square(Color color, float x_pos, float y_pos, Chesspiece* occupant = nullptr);

	void init() {};
	void draw();
	void update();

	
	float getPosX() { return m_pos[0]; }
	float getPosY() { return m_pos[1]; }

	void setPiece(Chesspiece* occupant);
	Chesspiece* getPiece() { return m_occupant; }
};

