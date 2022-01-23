#pragma once

#include <sgg/graphics.h>
#include <iostream>
#include <chrono>
#include <thread>

#define SETCOLOR(c, r, g, b) {c[0] = r; c[1] = g, c[2] = b;} // Easy function to set colour 

namespace global 
{

	/* Window Variables */
	namespace size {

		namespace window {
			inline constexpr char const* WINDOW_NAME{ "Chess v1.3" };

			inline constexpr unsigned WINDOW_WIDTH{ 1000 };
			inline constexpr unsigned WINDOW_HEIGHT{ 1000 };

			inline constexpr float CANVAS_WIDTH{ 1000.0f };
			inline constexpr float CANVAS_HEIGHT{ 1000.0f };
		}

		namespace objects {
			inline constexpr unsigned BOARD_WIDTH{ 8 };
			inline constexpr unsigned BOARD_HEIGHT{ 8 };

			inline constexpr float PIECE_WIDTH{ 100.0f };
			inline constexpr float PIECE_HEIGHT{ 100.0f };

			inline constexpr float SQUARE_WIDTH{ 100.0f };
			inline constexpr float SQUARE_HEIGHT{ 100.0f };
		}
	}

	/* PATH Constants */
	namespace path {

		/* Sound Effects */
		namespace sound {
			inline constexpr char const* MENU_MUSIC{ ".\\assets\\sounds\\menu_song.mp3" };

			inline constexpr char const* START_GAME_EFFECT{ ".\\assets\\sounds\\effects\\start_game.mp3" };
			inline constexpr char const* END_GAME_EFFECT{ ".\\assets\\sounds\\effects\\end_game.mp3" };
			inline constexpr char const* PIECE_MOVED_EFFECT{ ".\\assets\\sounds\\effects\\piece_moved.mp3" };
			inline constexpr char const* PIECE_CAPTURED_EFFECT{ ".\\assets\\sounds\\effects\\piece_captured.mp3" };
			inline constexpr char const* CHECK_EFFECT{ ".\\assets\\sounds\\effects\\check.mp3" };
		}

		/* Fonts */
		namespace font {
			inline constexpr char const* FONT_PATH{ ".\\assets\\fonts\\Helvetica.ttf" };
		}

		/* Textures */
		namespace textures {
			inline constexpr char const* LOGO_PATH{ ".\\assets\\sprites\\icons\\logo.png" };

			inline constexpr char const* SQUARES_PATH{ ".\\assets\\sprites\\squares\\" };
			inline constexpr char const* PIECES_PATH{ ".\\assets\\sprites\\chesspieces\\" };
			inline constexpr char const* ICONS_PATH{ ".\\assets\\sprites\\icons\\" };\

			inline constexpr char const* WHITE_SQUARE_PATH{ ".\\assets\\sprites\\squares\\w_square.png" };
			inline constexpr char const* BLACK_SQUARE_PATH{ ".\\assets\\sprites\\squares\\b_square.png" };

			inline constexpr char const* B_PAWN_PATH{ ".\\assets\\sprites\\chesspieces\\b_pawn.png" };
			inline constexpr char const* B_KING_PATH{ ".\\assets\\sprites\\chesspieces\\b_king.png" };
			inline constexpr char const* B_QUEEN_PATH{ ".\\assets\\sprites\\chesspieces\\b_queen.png" };
			inline constexpr char const* B_BISHOP_PATH{ ".\\assets\\sprites\\chesspieces\\b_bishop.png" };
			inline constexpr char const* B_KNIGHT_PATH{ ".\\assets\\sprites\\chesspieces\\b_knight.png" };
			inline constexpr char const* B_ROOK_PATH{ ".\\assets\\sprites\\chesspieces\\b_rook.png" };

			inline constexpr char const* W_PAWN_PATH{ ".\\assets\\sprites\\chesspieces\\w_pawn.png" };
			inline constexpr char const* W_KING_PATH{ ".\\assets\\sprites\\chesspieces\\w_king.png" };
			inline constexpr char const* W_QUEEN_PATH{ ".\\assets\\sprites\\chesspieces\\w_queen.png" };
			inline constexpr char const* W_BISHOP_PATH{ ".\\assets\\sprites\\chesspieces\\w_bishop.png" };
			inline constexpr char const* W_KNIGHT_PATH{ ".\\assets\\sprites\\chesspieces\\w_knight.png" };
			inline constexpr char const* W_ROOK_PATH{ ".\\assets\\sprites\\chesspieces\\w_rook.png" };
		}
	}

	/* Enums */
	namespace enums {

		// Game Mode 
		enum class Mode {
			MAIN_MENU,
			GAME
		};

		// Difficulty 
		enum class Difficulty {
			EASY,
			NORMAL
		};

		// Colour
		enum class Color {
			WHITE,
			BLACK
		};

		enum class State { 
			INIT, 
			LOADING, 
			PLAYING, 
			WHITE_WINS, 
			BLACK_WINS,
			STALEMATE,
			GAME_REVIEW
		};

		/* Open the MAIN MENU by default */
		inline Mode g_mode{ Mode::MAIN_MENU };				

		/* If we are on DEBUG mode, we need highlighting */
		#ifdef _DEBUG
				inline Difficulty g_diff{ Difficulty::EASY }; 
		#else
				inline Difficulty g_diff{ Difficulty::NORMAL };
		#endif
	}

	/* Functions */
	namespace functions {

		/* Awaits for ms*10^-3 seconds */
		inline void sleep(int ms) {
			std::this_thread::sleep_for(std::chrono::milliseconds(ms));
		}

		/* Calculates the distance between 2 coordinates */
		inline float distance(float x1, float y1, float x2, float y2) {
			float dx = x1 - x2;
			float dy = y1 - y2;
			return sqrtf(dx * dx + dy * dy);
		}

		/* Custom instanceof method from Java */
		template<typename Base, typename T>
		inline bool instanceof(const T* src) {
			return dynamic_cast<const Base*>(src) != nullptr;
		}
	}

	/* Structs */
	namespace structs {
		struct cords { 
			float x_pos; 
			float y_pos; 
		};
	}
}

/* Make our global constants easy to use everywhere */
/* Against best practices. Abusive usage of 'using namespace' - */
/* for the sake of easy debugging and navigation of the Project. */
using namespace global;	
using namespace global::size::window;
using namespace global::size::objects;

using namespace global::path;
using namespace global::path::font;
using namespace global::path::sound;
using namespace global::path::textures;

using namespace global::enums;
using namespace global::functions;
using namespace global::structs;