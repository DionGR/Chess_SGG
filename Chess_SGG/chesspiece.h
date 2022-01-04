#pragma once

#include <cmath>		// For movement calculations
#include <deque>		// For creating Chesspiece* type definitions

#include "material.h"

#include "square.h"

/**
* Chesspiece Abstract Class
*
* Provides a model for all our chesspieces, as well
* most of their instance methods and attributes.
*/
class Chesspiece : public Material {
protected:
	class Square* m_square;

	Chesspiece(Color color);
public:
	virtual bool canOccupy(const Square* square, Square* square_arr[BOARD_HEIGHT][BOARD_WIDTH]) = 0;

	void setPosX(float x) override;
	void setPosY(float x) override;
	void setSquare(Square* square);
	void setHighlight(bool highlighted);
	Square* getSquare() const;
};

/* Chesspiece* Deque and Deque Iterator Type Definitions */
using piecelist_t = std::deque<Chesspiece*>;
using piecelist_itr_t = std::deque<Chesspiece*>::iterator;
using piecelist_rvitr_t = std::deque<Chesspiece*>::reverse_iterator;