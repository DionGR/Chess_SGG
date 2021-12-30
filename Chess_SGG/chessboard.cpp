#include "chessboard.h"


Chessboard* Chessboard::m_instance = nullptr;


/* Constructs the Chessboard class once, returns the same instance afterwards. */
Chessboard* Chessboard::getInstance()
{
	if (!m_instance)
		m_instance = new Chessboard();
	return m_instance;
}


/* Releases the current active Chessboard instance, freeing all dynamic memory. */
void Chessboard::releaseInstance() {
	if (m_white) m_white->releaseInstance();
	if (m_black) m_black->releaseInstance();

	for (auto piece : m_b_pieces) 
		delete piece;
	for (auto piece : m_w_pieces) 
		delete piece;

	m_b_pieces.clear();
	m_w_pieces.clear();

	for (int i{ 0 }; i < 5; ++i)
		for (int j{ 0 }; j < 4; ++j)
			delete m_squares[i][j];

	if (m_instance) delete m_instance;
}


/* Initialize the Players, Squares and Chesspieces */
void Chessboard::init()
{
	/* Initialize the players */
	m_white = WhitePlayer::getInstance();
	m_black = BlackPlayer::getInstance();
	m_active_player = &m_white;									 // White plays first, set white to active


	/* Initialize the chessboard squares */
	Square* square;
	Chesspiece* piece;
	float width{ CANVAS_WIDTH / 2.81f };
	float height{ CANVAS_HEIGHT / 1.34f };
	bool black{ true };

	for (int i{ 0 }; i < 5; ++i, black = !black) {				  // Switch between black and white every iteration.	
		for (int j{ 0 }; j < 4; ++j, black = !black) {			  							

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


	/* Construct the chess pieces */
	m_w_pieces.push_back(new Rook(Color::WHITE));
	m_w_pieces.push_back(new Queen(Color::WHITE));
	m_w_pieces.push_back(new King(Color::WHITE));
	m_w_pieces.push_back(new Rook(Color::WHITE));
	for (int j{ 0 }; j < 4; ++j) {
		m_w_pieces.push_back(new Pawn(Color::WHITE));
		m_b_pieces.push_back(new Pawn(Color::BLACK));
	}	
	m_b_pieces.push_back(new Rook(Color::BLACK));
	m_b_pieces.push_back(new Queen(Color::BLACK));
	m_b_pieces.push_back(new King(Color::BLACK));
	m_b_pieces.push_back(new Rook(Color::BLACK));


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


/* Draws the chessboard's assets */
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
	Player* active_player = *m_active_player;
	bool player_moved;;

	/* Obsolete Update */
	//for (int i{ 0 }; i < 5; ++i) 
	//	for (int j{ 0 }; j < 4; ++j) 
	//		m_squares[i][j]->update();


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


	piecelist_itr_t piece_itr = m_w_pieces.begin();
	piecelist_t* piecelist = &m_w_pieces;
	for (int i{ 0 }; i < 2; ++i) {

		for (piece_itr; piece_itr != piecelist->end(); ++piece_itr) {
			Chesspiece* piece = *piece_itr;
			if (!piece->getSquare()) {
				piecelist->erase(piece_itr);
				delete piece;
				break;
			}
		}
		piece_itr = m_b_pieces.begin();
		piecelist = &m_b_pieces;
	}
}




