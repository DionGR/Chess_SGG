#include "square.h"

/* Constructs a square according to the arguments */
Square::Square(Color color, float x_pos, float y_pos, int i, int j):
	Material(x_pos, y_pos),
	m_indices {i, j}
{
	m_br.outline_opacity = 0.0f;

	init(color);
};


/* Initializes the squares' brush texture according to its colour */
void Square::init(Color color) {
	switch (color) {
		case(Color::WHITE):
			m_br.texture = WHITE_SQUARE_PATH;
			break;
		case(Color::BLACK):
			m_br.texture = BLACK_SQUARE_PATH;
			break;
	}
}


/* Draws the square at its assigned position */
void Square::draw()
{
	graphics::drawRect(m_pos[0], m_pos[1], 47.0f, 60.0f, m_br);
}


/* Obsolete Update */
[[Obsolete("Object does not need updating. Inherited from GameObject, no usage.", true)]]
void Square::update(){}


/* Getters and Setters */
void Square::setPiece(Chesspiece* occupant)
{
	if (m_occupant) m_occupant->setSquare(nullptr);	// If there is an existing occupant, set their square to null

	m_occupant = occupant;

	if (!occupant) return;

	m_occupant->setPosX(m_pos[0]);
	m_occupant->setPosY(m_pos[1]);
	m_occupant->setSquare(this);
}

void Square::setEmpty(){ m_occupant = nullptr; }
int Square::getIndexI() const { return m_indices[0]; }
int Square::getIndexJ() const { return m_indices[1]; }
Chesspiece* Square::getPiece() const { return m_occupant; }