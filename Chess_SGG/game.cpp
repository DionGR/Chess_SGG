#include "game.h"

Game* Game::m_instance = nullptr;


Game::~Game()
{
	if (m_board) m_board->releaseInstance();
}

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
	graphics::preloadBitmaps(SQUARES_PATH);
	graphics::preloadBitmaps(PIECES_PATH);
	graphics::preloadBitmaps(ICONS_PATH);
	sleep(1500); 

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
		{
			m_board->draw();

			/* Retire option */
			SETCOLOR(m_text_br.fill_color, 1.0f, 1.0f, 1.0f);

			graphics::MouseState mouse;
			graphics::getMouseState(mouse);

			float mouse_pos_x = graphics::windowToCanvasX(mouse.cur_pos_x);
			float mouse_pos_y = graphics::windowToCanvasY(mouse.cur_pos_y);

			if (mouse_pos_x < CANVAS_WIDTH / 2.f + 50.f && mouse_pos_x > CANVAS_WIDTH / 2.f - 50.f && mouse_pos_y > CANVAS_HEIGHT - SQUARE_HEIGHT / 1.35f && mouse_pos_y <  CANVAS_HEIGHT - SQUARE_HEIGHT / 2.f)
				SETCOLOR(m_text_br.fill_color, .4f, .75f, .5f);

			graphics::drawText(CANVAS_WIDTH / 2.f - 50.f, CANVAS_HEIGHT - SQUARE_HEIGHT / 2.f, 30.f, "RETIRE", m_text_br);

			return;
		}
		/* Win Screens */
		case State::BLACK_WINS:
			graphics::drawText(CANVAS_WIDTH/2.f - 110.f, CANVAS_HEIGHT/2.f, 40.f, "BLACK WINS", m_text_br);
			graphics::drawText(CANVAS_WIDTH/2.f - 180.f, CANVAS_HEIGHT - SQUARE_HEIGHT, 30.0f, "CLICK FOR GAME REVIEW...", m_text_br);
			graphics::drawText(CANVAS_WIDTH/2.f - 110.f, CANVAS_HEIGHT - SQUARE_HEIGHT / 2.f, 20.f, "PRESS SPACE TO EXIT...", m_text_br);
			return;
		case State::WHITE_WINS:
			graphics::drawText(CANVAS_WIDTH/2.f - 110.f, CANVAS_HEIGHT/2.f, 40.f, "WHITE WINS", m_text_br);
			graphics::drawText(CANVAS_WIDTH/2.f - 180.f, CANVAS_HEIGHT - SQUARE_HEIGHT, 30.0f, "CLICK FOR GAME REVIEW...", m_text_br);
			graphics::drawText(CANVAS_WIDTH/2.f - 110.f, CANVAS_HEIGHT - SQUARE_HEIGHT / 2.f, 20.f, "PRESS SPACE TO EXIT...", m_text_br);
			return;
		case State::STALEMATE:
			graphics::drawText(CANVAS_WIDTH / 2.f - 110.f, CANVAS_HEIGHT / 2.f, 40.f, "STALEMATE", m_text_br);
			graphics::drawText(CANVAS_WIDTH / 2.f - 180.f, CANVAS_HEIGHT - SQUARE_HEIGHT, 30.0f, "CLICK FOR GAME REVIEW...", m_text_br);
			graphics::drawText(CANVAS_WIDTH / 2.f - 110.f, CANVAS_HEIGHT - SQUARE_HEIGHT / 2.f, 20.f, "PRESS SPACE TO EXIT...", m_text_br);
			return;
		/* Game Review - Shows board and exit messages*/
		case State::GAME_REVIEW:
			m_board->draw(); // The board is only drawn, not updated.
			SETCOLOR(m_text_br.fill_color, 1.f, .0f, .0f);
			graphics::drawText(CANVAS_WIDTH/2.f - 90.f, SQUARE_HEIGHT/3.f, 30.f, "GAME REVIEW", m_text_br);
			SETCOLOR(m_text_br.fill_color, 1.f, 1.f, 1.f);
			graphics::drawText(CANVAS_WIDTH/2.f - 110.f, CANVAS_HEIGHT - SQUARE_HEIGHT/2.f, 20.f, "PRESS SPACE TO EXIT...", m_text_br);
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
		{
			m_board->update(m_state);

			/* Check if player retired. The other player wins then. */
			graphics::MouseState mouse;
			graphics::getMouseState(mouse);

			float mouse_pos_x = graphics::windowToCanvasX(mouse.cur_pos_x);
			float mouse_pos_y = graphics::windowToCanvasY(mouse.cur_pos_y);

			if (mouse.button_left_released && mouse_pos_x < CANVAS_WIDTH / 2.f + 50.f && mouse_pos_x > CANVAS_WIDTH / 2.f - 50.f && mouse_pos_y > CANVAS_HEIGHT - SQUARE_HEIGHT / 1.35f && mouse_pos_y < CANVAS_HEIGHT - SQUARE_HEIGHT / 2.f) {
				m_state = (m_board->getActivePlayer().getColor() == Color::WHITE ? State::BLACK_WINS : State::WHITE_WINS);
				SETCOLOR(m_text_br.fill_color, 1.0f, 1.0f, 1.0f);
			}
			return;
		}
		/* Game Finished. Allow for game review or exit */
		case State::BLACK_WINS:
		case State::WHITE_WINS:
		case State::STALEMATE:
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
