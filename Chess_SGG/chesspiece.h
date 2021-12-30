#pragma once

#include <cmath>
#include <deque>

#include "gameobject.h"
#include "material.h"

#include "square.h"

/**
* Chesspiece Abstract Class
*
* Provides a model for all our chesspieces, as well
* most of their instance methods and attributes.
*/
class Chesspiece : GameObject, public Material {
protected:
	graphics::Brush m_br;

	Color m_color;

	class Square* m_square;

	bool m_highlighted;

	Chesspiece(Color color);
	virtual void init() = 0;
public:
	void draw();
	void update();

	void setPosX(float x);
	void setPosY(float x);
	void setSquare(Square* square);
	void setHighlight(bool highlighted);
	Square* getSquare() const;
	const Color getColor() const;

	virtual bool canOccupy(Square* square, Square* square_arr[5][4]) = 0;
};

/* Chesspiece* Deque and Deque Iterator Type Definitions */
using piecelist_t = std::deque<Chesspiece*>;
using piecelist_itr_t = std::deque<Chesspiece*>::iterator;
using piecelist_rvitr_t = std::deque<Chesspiece*>::reverse_iterator;