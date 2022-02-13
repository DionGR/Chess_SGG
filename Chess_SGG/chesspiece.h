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
	const std::string m_name;
	const cords m_icon_pos;

	class Square* m_square;
	bool m_moved;

	Chesspiece(Color color, std::string name, float x_icon_pos, float y_icon_pos);
public:
	virtual bool canOccupy(const Square& square, Square* square_arr[BOARD_HEIGHT][BOARD_WIDTH]) = 0;

	void setPosX(float x) override;
	void setPosY(float y) override;
	void setSquare(Square& square);
	void setHighlight(bool highlighted);
	void setDead();
	void setMoved();
	bool hasMoved() const;
	Square* getSquare() const;
	std::string getName() const;
	cords getIconPos() const;
};

/* Chesspiece* Vector and Vector Iterator Type Definitions */
/* Why vector? Good caching locality (serial in memory), slow removal but removal is not as common, quick insertion in the end */
using piecelist_t = std::vector<Chesspiece*>;
using piecelist_itr_t = std::vector<Chesspiece*>::iterator;
using piecelist_rvitr_t = std::vector<Chesspiece*>::reverse_iterator;
