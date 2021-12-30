#pragma once

#include <sgg/graphics.h>
#include <iostream>
#include <chrono>
#include <thread>

#define SETCOLOR(c, r, g, b) {c[0] = r; c[1] = g, c[2] = b;} // Easy function to set colour 

namespace global 
{

	/* Window Variables */
	namespace window {
		inline constexpr char const* WINDOW_NAME{ "Silverman 4x5 Chess v0.1" };
		inline constexpr unsigned WINDOW_WIDTH{ 1300 };
		inline constexpr unsigned WINDOW_HEIGHT{ 950 };
		inline constexpr float CANVAS_WIDTH{ 500.0f };
		inline constexpr float CANVAS_HEIGHT{ 500.0f };
	}

	/* File Constants */
	namespace path {

		// Sound Effects
		namespace sound {
			inline constexpr char const* MENU_MUSIC{ ".\\assets\\sounds\\menu_song.mp3" };
			inline constexpr char const* START_GAME_EFFECT{ ".\\assets\\sounds\\effects\\start_game.mp3" };
		}

		// Fonts
		namespace font {
			inline constexpr char const* FONT_PATH{ ".\\assets\\fonts\\Helvetica.ttf" };
		}

		// Chesspiece/board Textures
		namespace game_objects {
			inline constexpr char const* BITMAP_PATH{ ".\\assets\\sprites\\" };

			inline constexpr char const* WHITE_SQUARE_PATH{ ".\\assets\\sprites\\squares\\w_square.png" };
			inline constexpr char const* BLACK_SQUARE_PATH{ ".\\assets\\sprites\\squares\\b_square.png" };

			inline constexpr char const* B_KING_PATH{ ".\\assets\\sprites\\chesspieces\\b_king.png" };
			inline constexpr char const* B_QUEEN_PATH{ ".\\assets\\sprites\\chesspieces\\b_queen.png" };
			inline constexpr char const* B_PAWN_PATH{ ".\\assets\\sprites\\chesspieces\\b_pawn.png" };
			inline constexpr char const* B_TOWER_PATH{ ".\\assets\\sprites\\chesspieces\\b_tower.png" };

			inline constexpr char const* W_KING_PATH{ ".\\assets\\sprites\\chesspieces\\w_king.png" };
			inline constexpr char const* W_QUEEN_PATH{ ".\\assets\\sprites\\chesspieces\\w_queen.png" };
			inline constexpr char const* W_PAWN_PATH{ ".\\assets\\sprites\\chesspieces\\w_pawn.png" };
			inline constexpr char const* W_TOWER_PATH{ ".\\assets\\sprites\\chesspieces\\w_tower.png" };
		}
	}

	/* Enums */
	namespace enums {

		// Game Mode 
		enum class Mode {
			MAIN_MENU,
			GAME
		};

		// Colour
		enum class Color {
			WHITE,
			BLACK
		};

		inline Mode g_mode{ Mode::MAIN_MENU };		// Open the MAIN MENU by default.
	}

	/* Functions */
	namespace functions {
		inline void sleep(int ms) {
			std::this_thread::sleep_for(std::chrono::milliseconds(ms));
		}
		inline float distance(float x1, float y1, float x2, float y2) {
			float dx = x1 - x2;
			float dy = y1 - y2;
			return sqrtf(dx * dx + dy * dy);
		}
	}
}


using namespace global;	// Make our global constants easy to use everywhere
using namespace global::window;

using namespace global::path;
using namespace global::path::font;
using namespace global::path::sound;
using namespace global::path::game_objects;

using namespace global::enums;
using namespace global::functions;