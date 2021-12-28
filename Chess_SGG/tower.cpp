#include "tower.h"

Tower::Tower(Color color) :
	Chesspiece(color)
{
	init();
}


void Tower::init()
{
	m_br.outline_opacity = 0.0f;

	switch (m_color) {
	case(Color::WHITE):
		m_br.texture = W_TOWER_PATH;
		break;
	case(Color::BLACK):
		m_br.texture = B_TOWER_PATH;
		break;
	}
}

void Tower::draw()
{
	float highlight = 1.0f * m_highlighted;
	m_br.outline_opacity = highlight;
	graphics::drawRect(m_pos[0], m_pos[1], 40.0f, 50.0f, m_br);
}

void Tower::update()
{
}
