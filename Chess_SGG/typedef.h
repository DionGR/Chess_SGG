#pragma once

namespace typedefs {

	namespace chessboard {
#include <deque>

#include "square.h"
#include "chesspiece.h"
		using squarelist_t = std::deque<Square*>;
		using squarelist_itr_t = std::deque<Square*>::iterator;
		using squarelist_rvitr_t = std::deque<Square*>::reverse_iterator;

		using piecelist_t = std::deque<Chesspiece*>;
		using piecelist_itr_t = std::deque<Chesspiece*>::iterator;
		using piecelist_rvitr_t = std::deque<Chesspiece*>::reverse_iterator;
	}
}