#pragma once
#include "chesspiece.h"

class Pawn: public Chesspiece
{
private:
	void init();
public:
	Pawn(Color color);
	void draw();
	void update();
};

