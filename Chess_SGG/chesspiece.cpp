#include "chesspiece.h"


/* Initialize our piece's color and brush's outline opacity. By default it isn't attached to a square */
Chesspiece::Chesspiece(Color color, std::string name, float x_icon_pos, float y_icon_pos) :
	Material{ color, 0.0f, 0.0f, PIECE_WIDTH, PIECE_HEIGHT },
	m_name{ name + std::to_string(static_cast<int>(color)) }, // Piece name + colour identifier (0 for white, 1 for black)
	m_square{ nullptr },
	m_icon_pos{x_icon_pos, y_icon_pos},
	m_moved{ false }
{}

/* Getters and Setters */
void Chesspiece::setHighlight(bool highlighted) { m_br.outline_opacity = highlighted; }
void Chesspiece::setPosX(float x)				{ m_pos.x_pos = x; }
void Chesspiece::setPosY(float y)				{ m_pos.y_pos = y; }
void Chesspiece::setSquare(Square& square)		{ m_square = &square; }
void Chesspiece::setDead()						{ m_square = nullptr; }
void Chesspiece::setMoved()						{ m_moved = true;  }
bool Chesspiece::hasMoved()		 const			{ return m_moved; }
Square* Chesspiece::getSquare()   const			{ return m_square; }
std::string Chesspiece::getName() const			{ return m_name; } 
cords Chesspiece::getIconPos()    const			{ return m_icon_pos;  }


