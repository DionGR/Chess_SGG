#pragma once

#include "gameobject.h"
#include "material.h"

#include "chesspiece.h"

class Square: GameObject, public Material
{
private:
	const int m_indices[2];

	class  Chesspiece* m_occupant;

	graphics::Brush m_br;
public:
	Square(Color color, float x_pos, float y_pos, int i, int j);

	void init(Color color);
	void draw();
	void update();

	void setPiece(Chesspiece* occupant);
	void setEmpty();
	Chesspiece* getPiece() const;
	int getIndexI() const;
	int getIndexJ() const;
};

