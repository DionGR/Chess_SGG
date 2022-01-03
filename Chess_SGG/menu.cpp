#include "menu.h"

Menu* Menu::m_instance = nullptr;

/* Constructs the Game class once, returns the same instance afterwards */
Menu* Menu::getInstance()
{
	if (!m_instance) 
		m_instance = new Menu();

	return m_instance;
}


/* Releases the current active menu instance, deallocating any dynamic memory */
void Menu::releaseInstance()
{
	if (m_instance) delete m_instance;
}


/* Initializes the main menu's look and sound */
void Menu::init()
{
	graphics::setFont(FONT_PATH);
	SoundHandler::menuMusic();

	/* Set our background to gray for the menu */
	graphics::Brush background_br;
	SETCOLOR(background_br.fill_color, 0.25f, 0.25f, 0.25f);
	graphics::setWindowBackground(background_br);

	/* Set our TEXT's brush colour to white */
	SETCOLOR(m_text_br.fill_color, 1.0f, 1.0f, 1.0f);
}


/* Draws the main menu */
void Menu::draw() 
{
	/* Print two difficulty options NORMAL and EASY */
	graphics::drawText(CANVAS_WIDTH / 2.4f, CANVAS_HEIGHT / 2.0f, 20.0f, "NORMAL", m_text_br);
	graphics::drawText(CANVAS_WIDTH / 2.25f, CANVAS_HEIGHT / 1.8f, 20.0f, "EASY", m_text_br);
}


/* Continuously updates, awaiting for user input */
void Menu::update()
{
	graphics::MouseState mouse;
	graphics::getMouseState(mouse);

	/* If the NORMAL/EASY buttons are clicked, set the GAMEMODE to game and close the menu. Set difficulty accordingly.*/
	if (mouse.button_left_released && mouse.cur_pos_x > WINDOW_WIDTH / 2.7f && mouse.cur_pos_x < WINDOW_WIDTH / 1.7f && mouse.cur_pos_y > WINDOW_HEIGHT / 2.15f && mouse.cur_pos_y < WINDOW_HEIGHT / 2.0f)
	{
		g_mode = Mode::GAME;							// Set the gamemode to GAME

		SoundHandler::stopMusic();
		SoundHandler::startGame();						// Play a sound effect when the game is started.
	}
	else if (mouse.button_left_released && mouse.cur_pos_x > WINDOW_WIDTH / 2.7f && mouse.cur_pos_x < WINDOW_WIDTH / 1.7f && mouse.cur_pos_y > WINDOW_HEIGHT / 2.15f && mouse.cur_pos_y < WINDOW_HEIGHT / 1.7f) {
		g_diff = Difficulty::EASY;						// Difficulty to EASY.
		g_mode = Mode::GAME;							

		SoundHandler::stopMusic();
		SoundHandler::startGame();						
	}
}