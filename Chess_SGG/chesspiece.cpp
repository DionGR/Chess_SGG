#include "chesspiece.h"


/* Initializes our piece's color and brush's outline opacity. By default it isn't attached to a square */
Chesspiece::Chesspiece(Color color) :
	m_color(color),
	m_square(nullptr),
	m_highlighted(false)
{
	m_br.outline_opacity = 0.0f;
}


/* Draws the piece. All pieces have the same brush apart from the texture, which is initialized in the subclasses */
void Chesspiece::draw() {
	float highlight = 1.0f * m_highlighted;
	m_br.outline_opacity = highlight;
	graphics::drawRect(m_pos[0], m_pos[1], 40.0f, 50.0f, m_br);
}


[[Obsolete("Object does not need updating. Inherited from GameObject, no usage.", true)]]
void Chesspiece::update() {}


/* Getters and Setters */
void Chesspiece::setPosX(float x) { m_pos[0] = x; }
void Chesspiece::setPosY(float x) { m_pos[1] = x; }
void Chesspiece::setSquare(Square* square) { m_square = square; }
void Chesspiece::setHighlight(bool highlighted) { m_highlighted = highlighted; }
Square* Chesspiece::getSquare() const { return m_square; }
const Color Chesspiece::getColor() const { return m_color; }
