#include "game.h"

Game* Game::m_instance = nullptr;


/* Constructs the Game class once, returns the same instance afterwards. */
Game* Game::getInstance()
{
	if (!m_instance)
		m_instance = new Game();
	return m_instance;
}


/* Releases the current active Game instance, freeing all dynamic memory. */
void Game::releaseInstance()
{
	if (m_board) m_board->releaseInstance();

	if (m_instance) delete m_instance;
}


/* Initializes the game's main components.*/
void Game::init()
{
	/* Set our font for the game  */
	graphics::setFont(FONT_PATH);

	/* Set our background to gray for the game */
	graphics::Brush background_br;
	SETCOLOR(background_br.fill_color, 0.25f, 0.25f, 0.25f);
	graphics::setWindowBackground(background_br);

	/* Set our TEXT's brush colour to white */
	m_text_br.outline_opacity = 0.0f;
	SETCOLOR(m_text_br.fill_color, 1.0f, 1.0f, 1.0f);

	/* Preload all the BITMAPs for better future loading */
	graphics::preloadBitmaps(static_cast<std::string>(BITMAP_PATH) + "\\squares\\");
	graphics::preloadBitmaps(static_cast<std::string>(BITMAP_PATH) + "\\chesspieces\\");
	//sleep(2000); 

	/* Initialize our gameboard and get the unique instance */
	m_board = Chessboard::getInstance();
	m_board->init();
	
	m_state = State::PLAYING;
}


/* Draws the game's assets */
void Game::draw()
{
	/* Depending on the state, draw the appropriate thing */
	switch (m_state){
		/* Loading Screen */
		case State::INIT:
			graphics::drawText(CANVAS_WIDTH/2.f - 180.f, CANVAS_HEIGHT/2.f, 40.f, "LOADING ASSETS...", m_text_br);
			m_state = State::LOADING;
			return;
		/* Game Board */
		case State::PLAYING: 
			m_board->draw();
			return;
		/* Win Screens */
		case State::BLACK_WINS:
			graphics::drawText(CANVAS_WIDTH/2.f - 110.f, CANVAS_HEIGHT/2.f, 40.f, "BLACK WINS", m_text_br);
			graphics::drawText(CANVAS_WIDTH/2.f - 180.f, CANVAS_HEIGHT - SQUARE_HEIGHT, 30.0f, "CLICK FOR GAME REVIEW...", m_text_br);
			graphics::drawText(CANVAS_WIDTH/2.f - 150.f, CANVAS_HEIGHT - SQUARE_HEIGHT/2.f, 30.f, "PRESS SPACE TO EXIT...", m_text_br);
			return;
		case State::WHITE_WINS:
			graphics::drawText(CANVAS_WIDTH/2.f - 110.f, CANVAS_HEIGHT/2.f, 40.f, "WHITE WINS", m_text_br);
			graphics::drawText(CANVAS_WIDTH/2.f - 180.f, CANVAS_HEIGHT - SQUARE_HEIGHT, 30.0f, "CLICK FOR GAME REVIEW...", m_text_br);
			graphics::drawText(CANVAS_WIDTH/2.f - 150.f, CANVAS_HEIGHT - SQUARE_HEIGHT/2.f, 30.f, "PRESS SPACE TO EXIT...", m_text_br);
			return;
		/* Game Review - Shows board and exit messages*/
		case State::GAME_REVIEW:
			m_board->draw(); // The board is only drawn, not updated.
			SETCOLOR(m_text_br.fill_color, 1.f, .0f, .0f);
			graphics::drawText(CANVAS_WIDTH/2.f - 90.f, SQUARE_HEIGHT/3.f, 30.f, "GAME REVIEW", m_text_br);
			SETCOLOR(m_text_br.fill_color, 1.f, 1.f, 1.f);
			graphics::drawText(CANVAS_WIDTH/2.f - 150.f, CANVAS_HEIGHT - SQUARE_HEIGHT/2.f, 30.f, "PRESS SPACE TO EXIT...", m_text_br);
			return;
	}	
}


/* Continuously updates, awaiting for user input. */
void Game::update()
{
	/* Depending on the state... */
	switch (m_state) {
		/* Do nothing and await for the game to start */
		case State::INIT:
			return;
		/* Initialize the game items */
		case State::LOADING:
			init();
			return;
		/* The board is active and able to change the state anytime, when the game finishes */
		case State::PLAYING:
			m_board->update(m_state);
			return;
		/* Game Finished. Allow for game review or exit */
		case State::BLACK_WINS:
		case State::WHITE_WINS:
			graphics::MouseState mouse;
			graphics::getMouseState(mouse);

			if (mouse.button_left_pressed) 
				m_state = State::GAME_REVIEW;
			__fallthrough;
		/* Allow for exit after the player is done reviewing */
		case State::GAME_REVIEW:
			/* Space Exits the Game on WINNING or REVIEW screen */
			if (graphics::getKeyState(graphics::SCANCODE_SPACE)) 
				graphics::stopMessageLoop();
			return;
	}
}
