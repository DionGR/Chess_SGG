#pragma once

#include "chesspiece.h"

class King: public Chesspiece
{
private:
	void init();
public:
	King(Color color);
	void draw();
	void update();
};

