#include "chessboard.h"


Chessboard* Chessboard::m_instance = nullptr;

/* Construct the Chessboard class once, returns the same instance afterwards. */
Chessboard* Chessboard::getInstance()
{
	if (!m_instance)
		m_instance = new Chessboard();
	return m_instance;
}


/* Release the current active Chessboard instance, freeing all dynamic memory. */
void Chessboard::releaseInstance()
{
	if (m_white) m_white->releaseInstance();
	if (m_black) m_black->releaseInstance();

	for (auto piece : m_b_pieces) 
		delete piece;
	for (auto piece : m_w_pieces) 
		delete piece;

	for (int i{ 0 }; i < BOARD_HEIGHT; ++i)
		for (int j{ 0 }; j < BOARD_WIDTH; ++j)
			delete m_squares[i][j];

	m_b_pieces.clear();
	m_w_pieces.clear();

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
	m_active_player = &m_white;												 // White plays first, set white to active


	/* Initialize the chessboard squares */
	Square* square;
	Chesspiece* piece;
	float width{ CANVAS_WIDTH / 2.81f };
	float height{ CANVAS_HEIGHT / 1.34f };
	bool black{ true };

	for (int i{ 0 }; i < BOARD_HEIGHT; ++i, black = !black) {				  // Switch between black and white every iteration.	
		for (int j{ 0 }; j < BOARD_WIDTH; ++j, black = !black) {			  							

			if (black)
				square = new Square(Color::BLACK, width, height, i, j);
			else
				square = new Square(Color::WHITE, width, height, i, j);

			m_squares[i][j] = square;
				
			width += 47.0f;											// Move right for the next square.
		}
		width = CANVAS_WIDTH / 2.81f;								// Reset width position for every line
		height -= 60.0f;											// Go to the line above
	}


	/* Construct the chess pieces and assign them to squares */
	m_w_pieces.push_back(new Rook(Color::WHITE));
	m_w_pieces.push_back(new Queen(Color::WHITE));
	m_w_pieces.push_back(new King(Color::WHITE));
	m_w_pieces.push_back(new Rook(Color::WHITE));
	for (int j{ 0 }; j < BOARD_WIDTH; ++j) {
		m_w_pieces.push_back(new Pawn(Color::WHITE));
		m_b_pieces.push_back(new Pawn(Color::BLACK));
	}	
	m_b_pieces.push_back(new Rook(Color::BLACK));
	m_b_pieces.push_back(new Queen(Color::BLACK));
	m_b_pieces.push_back(new King(Color::BLACK));
	m_b_pieces.push_back(new Rook(Color::BLACK));

	
	/* Assign the White pieces */
	piecelist_itr_t piece_itr = m_w_pieces.begin();
	for (int i{ 0 }; i < 2; ++i) {
		for (int j{ 0 }; j < 4; ++j) {
			piece = *piece_itr++;
			m_squares[i][j]->setPiece(piece);
			piece->setSquare(m_squares[i][j]);
		}
	}

	/* Assign the Black pieces */
	piecelist_rvitr_t piece_rvitr = m_b_pieces.rbegin();
	for (int i{ 4 }; i > 2; --i) {
		for (int j{ 3 }; j >= 0; --j) {
			piece = *piece_rvitr++;
			m_squares[i][j]->setPiece(piece);
			piece->setSquare(m_squares[i][j]);
		}
	}
}


/* Draw the chessboard's assets */
void Chessboard::draw()
{
	/* Draw the squares and reset Highlighting */
	for (int i{ 0 }; i < BOARD_HEIGHT; ++i)
		for (int j{ 0 }; j < BOARD_WIDTH; ++j) {
			m_squares[i][j]->draw();
			m_squares[i][j]->setHighlight();
		}
	

	// For Game Review Mode, active_player will be nullptr
	Player* active_player{ (m_active_player) ? *m_active_player : nullptr };
	Color active_color{ (active_player) ? active_player->getColor() : Color::BLACK};	

	/* Print in a different order so as to prevent piece shadowing depending on the turn */
	switch (active_color) {
		case Color::WHITE:
			for (auto piece : m_b_pieces)
				piece->draw();
			for (auto piece : m_w_pieces)
				piece->draw();
			break;
		case Color::BLACK:
			for (auto piece : m_w_pieces)
				piece->draw();
			for (auto piece : m_b_pieces)
				piece->draw();
			break;
	}

	/* Print the turns */
	graphics::drawText(CANVAS_WIDTH / 2.35f, CANVAS_HEIGHT / 1.17f, 20.0f, "TURN:" + std::to_string(m_turns), m_text_br);
}


/* Handles updating for all the on-board material assets as well as the Players */
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
					/* If the piece has no square assigned, play the captured sound effect and delete it from memory */
					if (!piece->getSquare()) {
						SoundHandler::pieceCaptured();
						piecelist->erase(piece_itr);
						/* If it's a king, change the gamestate and do not assign a next turn */
						if (instanceof<King>(piece)) {
							state = active_player->getColor() == Color::WHITE ? State::WHITE_WINS : State::BLACK_WINS;
							m_active_player = nullptr;
						}
						delete piece;
						return;
					}
				}
				SoundHandler::pieceMoved();
				piece_itr = m_b_pieces.begin();									// Swap to the black pieces 
				piecelist = &m_b_pieces;
			}
		}();
	}
}




