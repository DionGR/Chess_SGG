#include "menu.h"

Menu* Menu::m_instance = nullptr;

/* Constructs the Game class once, returns the same instance afterwards */
Menu* Menu::getInstance()
{
	if (!m_instance) 
		m_instance = new Menu();

	return m_instance;
}

/* Releases the current active menu instance, deallocating any heap memory */
void Menu::releaseInstance()
{
	if (m_instance) delete m_instance;
}


/* Initializes the main menu's look and sound */
void Menu::init()
{
	graphics::setFont(FONT_PATH);
	graphics::playMusic(MENU_MUSIC, 0.15f);
}


/* Draws the main menu */
void Menu::draw()
{
	graphics::Brush br;

	SETCOLOR(br.fill_color, 0.25f, 0.25f, 0.25f);
	graphics::setWindowBackground(br);													// Colour our background.
	
	
	SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
	graphics::drawText(CANVAS_WIDTH / 2.7, CANVAS_HEIGHT / 2, 20.0f, "START GAME", br);	// Print the Start Game text.
}


/* Continuously updates, awaiting for user input */
void Menu::update()
{
	graphics::MouseState mouse;
	graphics::getMouseState(mouse);

	if (mouse.button_left_released && mouse.cur_pos_x > WINDOW_WIDTH / 2.7f && mouse.cur_pos_x < WINDOW_WIDTH / 1.7f && mouse.cur_pos_y > WINDOW_HEIGHT / 2.15f && mouse.cur_pos_y < WINDOW_HEIGHT / 2.0f)
	{
		g_mode = Mode::GAME;							// Set the gamemode to GAME

		graphics::stopMusic();					
		graphics::playSound(START_GAME_EFFECT, 1.0f);	// Play a sound effect when the game is started.
	}// If the "Start Game" button is clicked, set the GAMEMODE to game and close the menu.

}