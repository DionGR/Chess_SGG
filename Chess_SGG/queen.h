#pragma once
#include "chesspiece.h"

class Queen: public Chesspiece
{
private:
	void init();
public:
	Queen(Color color);
	void draw();
	void update();
};

