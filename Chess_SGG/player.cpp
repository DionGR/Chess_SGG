#include "player.h"

/* Initializes a player's attributes */
Player::Player(Color color): 
	m_color{ color }, 
	m_active_piece{ nullptr } 
{}


/* Returns the player's colour */
Color Player::getColor() const {
	return m_color; 
}

/* Handles the movements a player may do with their pieces */
bool Player::update(const piecelist_t& pieces, Square* squares[BOARD_WIDTH][BOARD_HEIGHT])
{
	bool moved{ false };

	graphics::MouseState mouse;
	graphics::getMouseState(mouse);

	float x_pos{ graphics::windowToCanvasX(mouse.cur_pos_x) };
	float y_pos{ graphics::windowToCanvasY(mouse.cur_pos_y) };

	/* For every piece the player owns */
	for (auto& piece: pieces) {

#ifdef _DEBUG
		/* Highlight any piece the player hovers over(if they own it) */
		/* Only used for debugging as it is quite ugly */
		piece->setHighlight(piece->contains(x_pos, y_pos));	
#endif

		/* If the player is dragging a piece */
		if (mouse.button_left_down && piece->contains(x_pos, y_pos)) {

			/* Set it as active if there isn't another active one */
			if (!m_active_piece || m_active_piece == piece) {
				m_active_piece = piece;
				m_active_piece->setPosX(x_pos);
				m_active_piece->setPosY(y_pos);
				m_active_piece->getSquare()->setHighlight(true);		// Highlight the SOURCE square. Annotation is false, only if MALLOC fails.
			}

			/* If EASY, display all possible moves by highlighting the squares */
			if(g_diff == Difficulty::EASY)
				for (int i{ 0 }; i < BOARD_HEIGHT; ++i)
					for (int j{ 0 }; j < BOARD_WIDTH; ++j)
						if (m_active_piece->canOccupy(*squares[i][j], squares)) 
							squares[i][j]->setHighlight(true, squares[i][j]->hasEnemyOf(*m_active_piece), squares[i][j]->contains(x_pos, y_pos));
		}


		/* If the piece is dropped somewhere */
		if (mouse.button_left_released && m_active_piece == piece) {
			/* Lambda for breaking out of a double loop. No need to loop after a piece is moved. */
			[&] {
				/* For every square */
				for (int i{ 0 }; i < BOARD_HEIGHT; ++i) {
					for (int j{ 0 }; j < BOARD_WIDTH; ++j) {
						/* If the piece is on it */
						Square* square{ squares[i][j] };
						if (square->contains(m_active_piece->getPosX(), m_active_piece->getPosY())) {
							/* If the piece can occupy that square */
							if (m_active_piece->canOccupy(*square, squares)) {
								m_active_piece->getSquare()->setEmpty();					 // Set the piece's previous square to null
								square->setPiece(*m_active_piece);							 // Set the square's piece to the active piece
								moved = true;												 // Flag that the piece has moved for our update function.
								if (!m_active_piece->hasMoved()) m_active_piece->setMoved(); // Flag that our piece moved for special moves.
								return;
							}
							/* CASTLING - If we are moving the king for the first time*/
							else if (instanceof<King>(m_active_piece) && !m_active_piece->hasMoved()) {
								Chesspiece* target{ square->getPiece() };
								/* And the target is a friendly rook that hasn't been moved*/
								if (instanceof<Rook>(target) && m_active_piece->getColor() == target->getColor() && !target->hasMoved()) {
									int srcI{ m_active_piece->getSquare()->getIndexI() };
									int srcJ{ m_active_piece->getSquare()->getIndexJ() };
									int dstJ{ square->getIndexJ() };

									int kingDstJ{ (srcJ < dstJ) ? 6 : 2 };
									int rookDstJ{ (srcJ < dstJ) ? 5 : 3 };
									
									/* And there are no pieces inbetween */
									if (target->canOccupy(*squares[srcI][rookDstJ], squares) && squares[srcI][rookDstJ]->isEmpty()) {
										/* Perform castling between the king and the rook */
										m_active_piece->getSquare()->setEmpty();
										target->getSquare()->setEmpty();
										squares[srcI][kingDstJ]->setPiece(*m_active_piece);
										squares[srcI][rookDstJ]->setPiece(*target);

										moved = true;
										m_active_piece->setMoved();
										target->setMoved();
										return;
									}
								}
							}
						}
					}
				}
			}();
			/* Finally, the active piece should be on its square at all times. Works for both bad and good moves */
			if (m_active_piece) {	
				m_active_piece->setPosX(m_active_piece->getSquare()->getPosX());
				m_active_piece->setPosY(m_active_piece->getSquare()->getPosY());
				m_active_piece->setHighlight(false);
				m_active_piece = nullptr;
			}// Checking for NULL in case malloc fails
		}
	}
	return moved;
}