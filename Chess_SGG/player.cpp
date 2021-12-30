#include "player.h"


bool Player::update(piecelist_t& pieces, Square* squares[5][4])
{
	bool moved{ false };
	graphics::MouseState mouse;
	graphics::getMouseState(mouse);

	float x_pos = graphics::windowToCanvasX(mouse.cur_pos_x);
	float y_pos = graphics::windowToCanvasY(mouse.cur_pos_y);

	/* For every piece the player owns */
	for (auto piece: pieces) {

		// Highlight any piece the player hovers over (if they own it)
		piece->setHighlight(piece->contains(x_pos, y_pos));								

		/* If the player clicks on a piece, set it as active and attach it to the cursor */
		if (mouse.button_left_down && piece->contains(x_pos, y_pos)) {
			if (!m_active_piece || m_active_piece == piece) {
				m_active_piece = piece;
				m_active_piece->setPosX(x_pos);
				m_active_piece->setPosY(y_pos);
			}
		}

		/* If the piece is dropped somewhere */
		if (mouse.button_left_released && m_active_piece == piece) {
			/* For every square */
			for (int i{ 0 }; i < 5; ++i) {
				for (int j{ 0 }; j < 4; ++j) {
					/* If the piece is on a square */
					Square* square = squares[i][j];
					if (square->contains(m_active_piece->getPosX(), m_active_piece->getPosY())) {
						/* If the square is empty or there is an opponent */
						if (!square->getPiece() || square->getPiece()->getColor() != m_active_piece->getColor()) {
							/* And the piece can occupy that square */
							if (m_active_piece->canOccupy(square, squares)) {
								m_active_piece->getSquare()->setEmpty();								// Set the piece's previous square to null
								square->setPiece(m_active_piece);										// Set the square's piece to the active piece
								moved = true;
							}
						}
					}
				}
			}
			piece->setHighlight(false);
			/* Finally, the active piece should be on its square at all times */
			m_active_piece->setPosX(m_active_piece->getSquare()->getPosX());
			m_active_piece->setPosY(m_active_piece->getSquare()->getPosY());
			m_active_piece = nullptr;
		}
	}

	return moved;
}
