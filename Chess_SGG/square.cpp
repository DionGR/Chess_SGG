#include "square.h"

/* Constructs a square according to the arguments */
Square::Square(Color color, float x_pos, float y_pos, Chesspiece* occupant):
	m_pos {x_pos, y_pos},
	m_occupant {occupant}
{
	m_br.outline_opacity = 0.0f;

	switch (color) {
		case(Color::WHITE):
			m_br.texture = WHITE_SQUARE_PATH;
			break;
		case(Color::BLACK):
			m_br.texture = BLACK_SQUARE_PATH;
			break;
	}
};

void Square::draw()
{
	graphics::drawRect(m_pos[0], m_pos[1], 47.0f, 60.0f, m_br);
	if (m_occupant) m_occupant->draw();
}


void Square::update()
{
	if (m_occupant) m_occupant->update();
}

void Square::setPiece(Chesspiece* occupant)
{
	if (!m_occupant) {
		m_occupant = occupant;
		m_occupant->setPosX(m_pos[0]);
		m_occupant->setPosY(m_pos[1]);
		m_occupant->setSquare(this);
	}else {
		m_occupant = occupant;
	}

}
