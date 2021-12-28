#pragma once

#include "chesspiece.h"

class Tower: public Chesspiece
{
private:
	void init();
public:
	Tower(Color color);
	void draw();
	void update();
};

