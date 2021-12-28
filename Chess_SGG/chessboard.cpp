#include "chessboard.h"

Chessboard* Chessboard::m_instance = nullptr;

Chessboard* Chessboard::getInstance()
{
	if (!m_instance)
		m_instance = new Chessboard();
	return m_instance;
}// Constructs the Chessboard class once, returns the same instance afterwards.

void Chessboard::releaseInstance() {
	if (m_white) m_white->releaseInstance();
	if (m_black) m_black->releaseInstance();

	for (int i{ 0 }; i < 5; ++i)
		for (int j{ 0 }; j < 4; ++j)
			delete m_squares[i][j];

	for (auto piece : m_b_pieces) delete piece;
	for (auto piece : m_w_pieces) delete piece;

	m_b_pieces.clear();
	m_w_pieces.clear();

	if (m_instance) delete m_instance;
}

void Chessboard::init()
{
	/* Construct the players */
	m_white = WhitePlayer::getInstance();
	m_black = BlackPlayer::getInstance();
	m_active_player = &m_white;

	/* Construct the chessboard squares */
	float width{ CANVAS_WIDTH / 2.81f };
	float height{ CANVAS_HEIGHT / 1.34f };
	bool black{ true };
	Square* square{};
	Chesspiece* piece{};

	for (int i{ 0 }; i < 5; ++i, black = !black) {				
		width = CANVAS_WIDTH / 2.81f;							  // Reset width position for every line.

		for (int j{ 0 }; j < 4; ++j, black = !black) {			  // Switch between black and white every iteration.
													

			if (black)
				square = new Square(Color::BLACK, width, height);
			else
				square = new Square(Color::WHITE, width, height);

			m_squares[i][j] = square;
				
			width += 47.0f;											// Move right for the next square.
		}
		height -= 60.0f;											// Go up 1 square for the next line.
	}

	/* Construct the chess pieces */

	m_w_pieces.push_back(new Tower(Color::WHITE));
	m_w_pieces.push_back(new Queen(Color::WHITE));
	m_w_pieces.push_back(new King(Color::WHITE));
	m_w_pieces.push_back(new Tower(Color::WHITE));
	for (int j{ 0 }; j < 4; ++j) {
		m_w_pieces.push_back(new Pawn(Color::WHITE));
		m_b_pieces.push_back(new Pawn(Color::BLACK));
	}	
	m_b_pieces.push_back(new Tower(Color::BLACK));
	m_b_pieces.push_back(new Queen(Color::BLACK));
	m_b_pieces.push_back(new King(Color::BLACK));
	m_b_pieces.push_back(new Tower(Color::BLACK));


	/* Assign them to their starting square */
	
	

	//squarelist_itr_t square_itr = m_squares.begin();
	//squarelist_rvitr_t square_rvitr = m_squares.rbegin();

	//while (piece_itr != m_w_pieces.end()) {
	//	square = *square_itr;
	//	Chesspiece* pc = *piece_itr;
	//	square->setPiece(pc);
	//	pc->setSquare(square);
	//	++square_itr;
	//	++piece_itr;

	//	square = *square_rvitr;
	//	pc = *piece_rvitr;
	//	square->setPiece(pc);
	//	pc->setSquare(square);
	//	++square_rvitr;
	//	++piece_rvitr;
	//}

	piecelist_itr_t piece_itr = m_w_pieces.begin();
	for (int i{ 0 }; i < 2; ++i) {
		for (int j{ 0 }; j < 4; ++j) {
			piece = *piece_itr++;
			m_squares[i][j]->setPiece(piece);
			piece->setSquare(m_squares[i][j]);
		}
	}

	piecelist_rvitr_t piece_rvitr = m_b_pieces.rbegin();
	for (int i{ 4 }; i > 2; --i) {
		for (int j{ 3 }; j >= 0; --j) {
			piece = *piece_rvitr++;
			m_squares[i][j]->setPiece(piece);
			piece->setSquare(m_squares[i][j]);
		}
	}
}

void Chessboard::draw()
{
	for (int i{ 0 }; i < 5; ++i)
		for (int j{ 0 }; j < 4; ++j)
			m_squares[i][j]->draw();
	for (auto piece : m_w_pieces)
		piece->draw();
	for (auto piece : m_b_pieces)
		piece->draw();
	
}

void Chessboard::update()
{
	for (int i{ 0 }; i < 5; ++i) 
		for (int j{ 0 }; j < 4; ++j) 
			m_squares[i][j]->update();

	graphics::MouseState mouse;
	graphics::getMouseState(mouse);

	float x_pos = graphics::windowToCanvasX(mouse.cur_pos_x);
	float y_pos = graphics::windowToCanvasY(mouse.cur_pos_y);


	Player* current = *m_active_player;
	switch (current->getColor()) {
		case(Color::WHITE):
			current->update(m_w_pieces, m_squares);
			break;
		case(Color::BLACK):
			current->update(m_b_pieces, m_squares);
			break;
	}

	piecelist_itr_t piece_itr = m_w_pieces.begin();
	for (piece_itr; piece_itr != m_w_pieces.end(); ++piece_itr) {
		Chesspiece* piece = *piece_itr;
		if (!piece->getSquare()) {
			m_w_pieces.erase(piece_itr);
			delete piece;
			break;
		}
		if (piece->m_moved) {
			m_active_player = &m_black;
			piece->m_moved = false;
		}
	}

	piece_itr = m_b_pieces.begin();
	for (piece_itr; piece_itr != m_b_pieces.end(); ++piece_itr) {
		Chesspiece* piece = *piece_itr;
		if (!piece->getSquare()) {
			m_b_pieces.erase(piece_itr);
			delete piece;
			break;
		}
		if (piece->m_moved) {
			m_active_player = &m_white;
			piece->m_moved = false;
		}
	}
}


