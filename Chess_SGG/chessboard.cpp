#include "chessboard.h"

Chessboard* Chessboard::m_instance = nullptr;

Chessboard::Chessboard() :
	m_turns{ 0 },
	m_white{ nullptr },
	m_black{ nullptr },
	m_active_player{ nullptr },
	m_squares{}
{};

/* Frees all the dynamically allocated memory for this object.*/
Chessboard::~Chessboard()
{
	if (m_white) m_white->releaseInstance();
	if (m_black) m_black->releaseInstance();

	for (auto& piece : m_b_pieces)
		delete piece;
	for (auto& piece : m_w_pieces)
		delete piece;

	for (int i{ 0 }; i < BOARD_HEIGHT; ++i)
		for (int j{ 0 }; j < BOARD_WIDTH; ++j)
			delete m_squares[i][j];

	m_b_pieces.clear();
	m_w_pieces.clear();
}

/* Construct the Chessboard class once, returns the same instance afterwards. */
Chessboard* Chessboard::getInstance()
{
	if (!m_instance)
		m_instance = new Chessboard();
	return m_instance;
}


/* Release the current active Chessboard instance. */
void Chessboard::releaseInstance()
{
	if (m_instance) delete m_instance;
}


/* Initialize the Players, Squares and Chesspieces */
void Chessboard::init()
{
	/* Initialize the text brush */
	graphics::Brush m_text_br;
	m_text_br.outline_opacity = 0.0f;
	SETCOLOR(m_text_br.fill_color, 1.0f, 1.0f, 1.0f);

	/* Initialize the players */
	m_white = WhitePlayer::getInstance();
	m_black = BlackPlayer::getInstance();
	m_active_player = &m_white;				// White plays first, set white to active									 


	/* Multithreading practice */
	/* Runtime is slower with multithreading for such small functions, */
	/* only done for practising purposes. */

	/* Initialize the chessboard squares */
	std::thread board_thread{ &generateBoard, std::ref(m_squares) };

	/* Construct the chess pieces */
	std::thread white_thread{ &generatePieces, Color::WHITE, std::ref(m_w_pieces) };
	std::thread black_thread{ &generatePieces, Color::BLACK, std::ref(m_b_pieces) };

	board_thread.join();
	black_thread.join();
	white_thread.join();

	/* Initialize the captured maps */
	std::thread w_captured_thread{ &initCaptured, std::ref(m_w_pieces), std::ref(m_captured) };
	std::thread b_captured_thread{ &initCaptured, std::ref(m_b_pieces), std::ref(m_captured) };

	/* Assign the pieces to their squares */
	std::thread assign_thread{ &assignPieces, std::ref(m_w_pieces), std::ref(m_b_pieces), std::ref(m_squares) };

	w_captured_thread.join();
	b_captured_thread.join();
	assign_thread.join();
}


/* Draw the chessboard's assets */
void Chessboard::draw()
{
	/* Draw the squares and reset Highlighting */
	for (int i{ 0 }; i < BOARD_HEIGHT; ++i) {
		for (int j{ 0 }; j < BOARD_WIDTH; ++j) {
			m_squares[i][j]->draw();
			m_squares[i][j]->setHighlight();
		}
	}

	// For Game Review Mode, active_player will be nullptr
	Player* active_player{ (m_active_player) ? *m_active_player : nullptr };
	Color active_color{ (active_player) ? active_player->getColor() : Color::BLACK };

	/* Draw the pieces */
	/* in a different order so as to prevent piece shadowing depending on the turn */
	switch (active_color) {
	case Color::WHITE:
		for (auto const& piece: m_b_pieces)
			piece->draw();
		for (auto const& piece: m_w_pieces)
			piece->draw();
		break;
	case Color::BLACK:
		for (auto const& piece: m_w_pieces)
			piece->draw();
		for (auto const& piece: m_b_pieces)
			piece->draw();
		break;
	}

	/* Draw the captured pieces icons */
	for (auto& captured : m_captured) {
		int captured_count{ captured.second.first };

		/* If a piece is captured at least once */
		if (captured_count) {
			std::string name{ captured.first };

			graphics::Brush icon_brush;
			icon_brush.outline_opacity = 0.f;

			/* Load the corresponding texture with a unique name and draw it */
			icon_brush.texture = ICONS_PATH + name + std::to_string(captured_count) + ".png";
			graphics::drawRect(captured.second.second.x_pos, captured.second.second.y_pos, 128, 32, icon_brush);
		}
	}

	/* Draw the turn counter */
	graphics::drawText(CANVAS_WIDTH / 2.f - 50.f, SQUARE_HEIGHT / 1.5f, 30.f, "TURN: " + std::to_string(m_turns), m_text_br);
}



/* Handle updating for all the on-board material assets as well as the Players */
void Chessboard::update(State& state)
{
	Player* active_player = *m_active_player;
	bool player_moved{ false };

	/* The active player can play here. If he moves, the turns switch */
	switch (active_player->getColor()) {
	case(Color::WHITE):
		player_moved = active_player->update(m_w_pieces, m_squares);
		if (player_moved) m_active_player = &m_black;
		break;
	case(Color::BLACK):
		player_moved = active_player->update(m_b_pieces, m_squares);
		if (player_moved) m_active_player = &m_white;
		break;
	}


	/* If the player moved */
	if (player_moved) {
		++m_turns;
		/* Check for captured pieces. Delete them from memory. */
		/* Lambda for breaking out of a double loop. No need to loop after a piece is deleted */
		[&] {
			piecelist_itr_t piece_itr = m_w_pieces.begin();						// Start with the white pieces
			piecelist_t* piecelist = &m_w_pieces;
			for (int i{ 0 }; i < 2; ++i) {
				/* For every piece in the list */
				for (piece_itr; piece_itr != piecelist->end(); ++piece_itr) {
					Chesspiece* piece = *piece_itr;
					/* If the piece has no square assigned */
					if (!piece->getSquare()) {
						piecelist->erase(piece_itr);

						/* If it's a king, change the gamestate and do not assign a next turn */
						if (instanceof<King>(piece)) {
							state = active_player->getColor() == Color::WHITE ? State::WHITE_WINS : State::BLACK_WINS;
							m_active_player = nullptr;
						}

						/* Increase the amount of captured pieces of this type */
						capturemap_t* captured{ &m_captured };
						std::string captured_name{ piece->getName() };

						/* Check for queen (we can spawn multiple but only show 1) or King (shouldn't be added to the map) */
						if ((!instanceof<King>(piece) && !instanceof<Queen>(piece)) || instanceof<Queen>(piece) && (*captured)[captured_name].first < 1)
							(*captured)[captured_name].first += 1;


						/* Delete the piece from memory and play the captured sound effect */
						delete piece;
						SoundHandler::pieceCaptured();


						/* If the 2 kings are the only pieces alive (cannot be of size 1 any other way), STALEMATE */
						if (m_b_pieces.size() == 1 && m_w_pieces.size() == 1) {
							state = State::STALEMATE;
							m_active_player = nullptr;
						}

						return;
					}
					/* If the king is threatened, play the check sound effect */
					if (instanceof<King>(piece) && piece->getColor() != active_player->getColor()) {
						King* king = dynamic_cast<King*>(piece);
						piecelist_t enemies{ (king->getColor() == Color::WHITE) ? m_b_pieces : m_w_pieces };
						if (king->isThreatened(enemies, m_squares))
							SoundHandler::check();
					}
					/* If the piece is a pawn and on enemy's side, spawn a Queen on its position */
					if (instanceof<Pawn>(piece) && (piece->getSquare()->getIndexI() == 0 || piece->getSquare()->getIndexI() == 7)) {
						*piece_itr = new Queen(piece->getColor());
						Chesspiece* new_piece = *piece_itr;
						piece->getSquare()->setPiece(*new_piece);
						delete piece;
					}
				}
				SoundHandler::pieceMoved();
				piece_itr = m_b_pieces.begin();									// Swap to the black pieces 
				piecelist = &m_b_pieces;
			}
		}();
	}
}


/* Return the active player*/
Player& Chessboard::getActivePlayer() const
{
	return **m_active_player;
}


/* HELPER FUNCTIONS */

/* HELPER - Generates all the squares in our board */
void Chessboard::generateBoard(Square* squares[BOARD_HEIGHT][BOARD_WIDTH])
{
	float width{ SQUARE_WIDTH * 1.5f };	// 1 Square gap from the borders
	float height{ CANVAS_HEIGHT - SQUARE_WIDTH * 1.5f };
	bool black{ true };

	for (int i{ 0 }; i < BOARD_HEIGHT; ++i, black = !black) {				  // Switch between black and white every iteration.	
		for (int j{ 0 }; j < BOARD_WIDTH; ++j, black = !black) {

			if (black)
				squares[i][j] = new Square(Color::BLACK, width, height, i, j);
			else
				squares[i][j] = new Square(Color::WHITE, width, height, i, j);

			width += SQUARE_WIDTH;											// Move right for the next square.
		}
		width = SQUARE_WIDTH * 1.5f;										// Reset width position for every line
		height -= SQUARE_HEIGHT;											// Go to the line above
	}
}

/* HELPER - Generate pieces of specific colour into the given piecelist_t */
void Chessboard::generatePieces(Color color, piecelist_t& piecelist)
{
	piecelist.push_back(new Rook(color));
	piecelist.push_back(new Knight(color));
	piecelist.push_back(new Bishop(color));
	piecelist.push_back(new Queen(color));
	piecelist.push_back(new King(color));
	piecelist.push_back(new Bishop(color));
	piecelist.push_back(new Knight(color));
	piecelist.push_back(new Rook(color));
	for (int i{ 0 }; i < BOARD_WIDTH; ++i)
		piecelist.push_back(new Pawn(color));
}

/* HELPER - Assign all the pieces to their respective squares geometrically */
void Chessboard::assignPieces(piecelist_t& w_pieces, piecelist_t& b_pieces, Square* squares[BOARD_HEIGHT][BOARD_WIDTH]) {

	/* Iterator Practice. Square assignment could happen in the piece's constructor. */

	/* Assign the White pieces */
	piecelist_itr_t piece_itr = w_pieces.begin();
	for (int i{ 0 }; i < 2; ++i)
		for (int j{ 0 }; j < BOARD_WIDTH; ++j)
			squares[i][j]->setPiece(**piece_itr++);

	/* Assign the Black pieces */
	piecelist_rvitr_t piece_rvitr = b_pieces.rbegin();
	for (int i{ BOARD_HEIGHT - 2 }; i < BOARD_HEIGHT; ++i)
		for (int j{ BOARD_WIDTH - 1 }; j >= 0; --j)
			squares[i][j]->setPiece(**piece_rvitr++);
}

/* HELPER - Initialize the captured list */
void Chessboard::initCaptured(piecelist_t& piecelist, capturemap_t& captured) {

	/* For every piece in the piecelist */
	for (auto const& piece : piecelist) {
		std::string name{ piece->getName() };
		/* If it's not already in and it isn't a King*/
		/* Initialize 0 (captured #) and the cords for the icon */
		if (captured.count(name) == 0 && !instanceof<King>(piece))
			captured[name] = std::make_pair(0, piece->getIconPos());
	}
}