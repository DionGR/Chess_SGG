#pragma once

#include "material.h"

#include "chesspiece.h"

/**
* Square Class
*
* Handles the Square's attributes.
*/
class Square: public Material
{
private:
	class  Chesspiece* m_occupant;

	const cords m_pos;
	const int m_indices[2];
public:
	Square(Color color, float x_pos, float y_pos, int i, int j);

	void init() override;

	bool hasEnemyOf(const Chesspiece& piece) const;
	bool isEmpty() const;

	void setPiece(Chesspiece& occupant);
	void setEmpty();
	void setHighlight(bool highlighted = false, bool enemy = false, bool hovering = false);
	Chesspiece* getPiece() const;
	int getIndexI() const;
	int getIndexJ() const;
};

