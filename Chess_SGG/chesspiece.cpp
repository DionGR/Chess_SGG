#include "chesspiece.h"


/* Initialize our piece's color and brush's outline opacity. By default it isn't attached to a square */
Chesspiece::Chesspiece(Color color) :
	Material{ color, 0.0f, 0.0f, PIECE_WIDTH, PIECE_HEIGHT },
	m_square{nullptr}
{}


/* Getters and Setters */
void Chesspiece::setHighlight(bool highlighted) { m_br.outline_opacity = highlighted; }
void Chesspiece::setPosX(float x)				{ m_pos[0] = x; }
void Chesspiece::setPosY(float x)				{ m_pos[1] = x; }
void Chesspiece::setSquare(Square* square)		{ m_square = square; }
Square* Chesspiece::getSquare() const			{ return m_square; }
