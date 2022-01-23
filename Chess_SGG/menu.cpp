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
	/* Set our font for the menu on and play the background music */
	graphics::setFont(FONT_PATH);
	SoundHandler::menuMusic();

	/* Set our background to gray for the menu */
	graphics::Brush background_br;
	SETCOLOR(background_br.fill_color, 0.25f, 0.25f, 0.25f);
	graphics::setWindowBackground(background_br);

	/* Set our main menu logo */
	m_logo_br.texture = LOGO_PATH;
	m_logo_br.outline_opacity = 0.f;
}


/* Draws the main menu */
void Menu::draw() 
{
	/* Main Menu Logo */
	graphics::drawRect(CANVAS_WIDTH / 2.f, CANVAS_HEIGHT / 4.f, 512, 256, m_logo_br);

	/* Options */
	graphics::MouseState mouse;
	graphics::getMouseState(mouse);

	float mouse_pos_x = graphics::windowToCanvasX(mouse.cur_pos_x);
	float mouse_pos_y = graphics::windowToCanvasY(mouse.cur_pos_y);

	graphics::Brush normal_br;
	graphics::Brush easy_br;

	SETCOLOR(normal_br.fill_color, 1.0f, 1.0f, 1.0f);
	SETCOLOR(easy_br.fill_color, 1.0f, 1.0f, 1.0f);

	/* Print two difficulty options NORMAL and EASY, in green if hovering */
	if( mouse_pos_x > CANVAS_WIDTH / 2.f - 90.f && mouse_pos_x < CANVAS_WIDTH / 2.f + 75.f && mouse_pos_y > CANVAS_HEIGHT / 2.f - 35.f && mouse_pos_y < CANVAS_HEIGHT / 2.f)
		SETCOLOR(normal_br.fill_color, .4f, .75f, .5f);

	graphics::drawText(CANVAS_WIDTH/2.f - 80.f, CANVAS_HEIGHT/2.f, 40.f, "NORMAL", normal_br);

	if (mouse_pos_x > CANVAS_WIDTH / 2.f - 50.f && mouse_pos_x < CANVAS_WIDTH / 2.f + 40.f && mouse_pos_y > CANVAS_HEIGHT / 2.f && mouse_pos_y < CANVAS_HEIGHT / 2.f + 50.f)
		SETCOLOR(easy_br.fill_color, .4f, .75f, .5f);

	graphics::drawText(CANVAS_WIDTH/2.f - 55.f, CANVAS_HEIGHT/2.f + 50.f, 40.f, "EASY", easy_br);
}


/* Continuously updates, awaiting for user input */
void Menu::update()
{
	graphics::MouseState mouse;
	graphics::getMouseState(mouse);

	/* For resizing compatability */
	float mouse_pos_x = graphics::windowToCanvasX(mouse.cur_pos_x);
	float mouse_pos_y = graphics::windowToCanvasY(mouse.cur_pos_y);

	/* If the NORMAL/EASY buttons are clicked, set the GAMEMODE to game and close the menu. Set difficulty accordingly */
	if (mouse.button_left_released && mouse_pos_x > CANVAS_WIDTH / 2.f - 90.f && mouse_pos_x < CANVAS_WIDTH / 2.f + 75.f && mouse_pos_y > CANVAS_HEIGHT / 2.f - 35.f && mouse_pos_y < CANVAS_HEIGHT / 2.f)
	{
		g_mode = Mode::GAME;							// Set the gamemode to GAME

		SoundHandler::stopMusic();
		SoundHandler::startGame();						// Play a sound effect when the game is started.
	}
	else if (mouse.button_left_released && mouse_pos_x > CANVAS_WIDTH / 2.f - 50.f && mouse_pos_x < CANVAS_WIDTH / 2.f + 40.f && mouse_pos_y > CANVAS_HEIGHT / 2.f && mouse_pos_y < CANVAS_HEIGHT / 2.f + 50.f) 
	{
		g_diff = Difficulty::EASY;						// Difficulty to EASY.

		g_mode = Mode::GAME;

		SoundHandler::stopMusic();
		SoundHandler::startGame();
	}
}