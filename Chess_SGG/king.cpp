#include "king.h"


King::King(Color color) :
	Chesspiece(color)
{
	init();
}


void King::init()
{
	
	switch (m_color) {
	case(Color::WHITE):
		m_br.texture = W_KING_PATH;
		break;
	case(Color::BLACK):
		m_br.texture = B_KING_PATH;
		break;
	}
}



void King::draw()
{
	float highlight = 1.0f * m_highlighted;
	m_br.outline_opacity = highlight;
	graphics::drawRect(m_pos[0], m_pos[1], 40.0f, 50.0f, m_br);
}



void King::update()
{
}
