#include "game.h"

Game* Game::m_instance = nullptr;


/* Constructs the Game class once, returns the same instance afterwards. */
Game* Game::getInstance()
{
	if (!m_instance)
		m_instance = new Game();
	return m_instance;
}


/* Releases the current active game instance, freeing all dynamic memory. */
void Game::releaseInstance()
{
	if (m_board) m_board->releaseInstance();


	if (m_instance) delete m_instance;
}


/* Initializes the game's main components.*/
void Game::init()
{
	graphics::preloadBitmaps(static_cast<std::string>(BITMAP_PATH) + "\\squares\\");
	graphics::preloadBitmaps(static_cast<std::string>(BITMAP_PATH) + "\\chesspieces\\");
	//sleep(2000);

	m_board = Chessboard::getInstance();
	m_board->init();
	
	m_state = State::IDLE;
}


/* Continuously updates, awaiting for user input. */
void Game::update()
{
	if (m_state == State::INIT)	return;
	if (m_state == State::LOADING) {
		init();
		return;
	}

	m_board->update(); 
}


/* Draws the game's assets */
void Game::draw()
{
	/* Background */
	graphics::Brush br;
	br.outline_opacity = 0.0f;
	SETCOLOR(br.fill_color, 0.25f, 0.25f, 0.25f);
	graphics::setWindowBackground(br);

	if (m_state == State::INIT)
	{
		SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
		graphics::setFont(FONT_PATH);
		graphics::drawText(CANVAS_WIDTH / 3.1, CANVAS_HEIGHT / 2, 20.0f, "LOADING ASSETS...", br);
		m_state = State::LOADING;
		return;
	}// Draw the loading screen.




	/* Gameboard */
	m_board->draw();

}



