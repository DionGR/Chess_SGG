#include "player.h"


void Player::update(piecelist_t& pieces, Square* squares[5][4])
{
	graphics::MouseState mouse;
	graphics::getMouseState(mouse);

	float x_pos = graphics::windowToCanvasX(mouse.cur_pos_x);
	float y_pos = graphics::windowToCanvasY(mouse.cur_pos_y);

	for (auto piece : pieces) {

		piece->setHighlight(piece->contains(x_pos, y_pos));

		if (mouse.button_left_down && piece->contains(x_pos, y_pos)) {
			if (!m_active_piece || m_active_piece == piece) {
				m_active_piece = piece;
				m_active_piece->setPosX(x_pos);
				m_active_piece->setPosY(y_pos);
			}
		}

		if (mouse.button_left_released && m_active_piece == piece) {
			for (int i{ 0 }; i < 5; ++i) {
				for (int j{ 0 }; j < 4; ++j) {
					if (piece->contains(squares[i][j]->getPosX(), squares[i][j]->getPosY())) {
						if (!squares[i][j]->getPiece()) {
							m_active_piece->getSquare()->setPiece(nullptr);
							squares[i][j]->setPiece(m_active_piece);
							m_active_piece->m_moved = true;
						}
						else if (squares[i][j]->getPiece()->getColor() != m_active_piece->getColor()) {
							m_active_piece->getSquare()->setPiece(nullptr);
							Chesspiece* enemy = squares[i][j]->getPiece();
							enemy->setSquare(nullptr);
							squares[i][j]->setPiece(nullptr);
							squares[i][j]->setPiece(m_active_piece);
							m_active_piece->m_moved = true;
						}
					}
				}
			}
			m_active_piece->setPosX(m_active_piece->getSquare()->getPosX());
			m_active_piece->setPosY(m_active_piece->getSquare()->getPosY());
			m_active_piece = nullptr;
			break;
		}
	}
}
