#include "pawn.h"

Pawn::Pawn(Color color) :
	Chesspiece(color)
{
	init();
}

void Pawn::init()
{
	m_br.outline_opacity = 0.0f;

	switch (m_color) {
	case(Color::WHITE):
		m_br.texture = W_PAWN_PATH;
		break;
	case(Color::BLACK):
		m_br.texture = B_PAWN_PATH;
		break;
	}
}

void Pawn::draw()
{
	float highlight = 1.0f * m_highlighted;
	m_br.outline_opacity = highlight;
	graphics::drawRect(m_pos[0], m_pos[1], 40.0f, 50.0f, m_br);
}


void Pawn::update()
{
}