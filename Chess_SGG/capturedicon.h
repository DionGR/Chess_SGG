#pragma once

#include "global.h"

class Capturedicon
{
private:
	graphics::Brush m_br;

	unsigned m_count;
public:
	Capturedicon() : m_count{ 0 } {};
};