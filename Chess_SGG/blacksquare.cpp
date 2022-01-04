#include "blacksquare.h"

void BlackSquare::draw()
{
	graphics::Brush br;
	SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
	br.outline_opacity = 0.0f;
	br.texture = ".\\assets\\b_square.png";
	graphics::drawRect(CANVAS_HEIGHT / 2, CANVAS_WIDTH / 2, 30.0f, 40.0f, br);
}
