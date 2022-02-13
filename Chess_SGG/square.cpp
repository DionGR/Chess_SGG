#include "square.h"

/* Constructs a square according to the arguments */
Square::Square(Color color, float x_pos, float y_pos, int i, int j):
	Material(color, x_pos, y_pos, SQUARE_WIDTH, SQUARE_HEIGHT),
	m_indices {i, j},
	m_pos{x_pos, y_pos}
{
	init();
};


/* Initializes the squares' brush texture according to its colour */
void Square::init() {
	switch (m_color) {
		case(Color::WHITE):
			m_br.texture = WHITE_SQUARE_PATH;
			break;
		case(Color::BLACK):
			m_br.texture = BLACK_SQUARE_PATH;
			break;
	}
}


/* Check whether this square contains an enemy of the incoming piece */
bool Square::hasEnemyOf(const Chesspiece& piece) const
{
	if (m_occupant)
		return piece.getColor() != m_occupant->getColor();

	return false;
}


/* Check if the square has an occupant */
bool Square::isEmpty() const
{
	return !m_occupant;
}


/* Getters and Setters */
void Square::setPiece(Chesspiece& occupant)
{
	if (m_occupant) m_occupant->setDead();	// If there is an existing occupant, set their square to null

	m_occupant = &occupant;

	m_occupant->setPosX(m_pos.x_pos);
	m_occupant->setPosY(m_pos.y_pos);
	m_occupant->setSquare(*this);
}

void Square::setHighlight(bool highlighted, bool enemy, bool hovering) {
	SETCOLOR(m_br.fill_color, 1.0f, !enemy, !highlighted);

	/* Outline the square when a piece is hovering over it, checked by the bool */
	m_br.outline_opacity = hovering;
	m_br.outline_width = 1.5f * hovering;
	SETCOLOR(m_br.outline_color, !hovering, !hovering, !hovering);
}

void Square::setEmpty()				 { m_occupant = nullptr; }
int Square::getIndexI()		   const { return m_indices[0]; }
int Square::getIndexJ()        const { return m_indices[1]; }
Chesspiece* Square::getPiece() const { return m_occupant; }