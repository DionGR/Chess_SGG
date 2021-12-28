#include "game.h"
#include "menu.h"

void draw() 
{
	switch (g_mode)
	{
		case Mode::GAME:
		{
			Game* game = Game::getInstance();
			game->draw();
			break;
		}
		case Mode::MAIN_MENU:
		{
			Menu* menu = Menu::getInstance();
			menu->draw();
			break;
		}
	}
}

void update(float ms)
{
	switch (g_mode) 
	{
		case Mode::GAME:
		{
			Game* game = Game::getInstance();
			game->update();
			break;
		}
		case Mode::MAIN_MENU:
		{
			Menu* menu = Menu::getInstance();
			menu->update();
			break;
		}
	}
}

int main(int argc, char** argv)
{
	Menu* menu{ Menu::getInstance() };
	Game* game{ Game::getInstance() };

	graphics::createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME);
	graphics::setCanvasSize(CANVAS_WIDTH, CANVAS_WIDTH);
	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_STRETCH);

	menu->init();
	
	graphics::setUserData(game);
	graphics::setDrawFunction(draw);
	graphics::setUpdateFunction(update);
	graphics::startMessageLoop();

	
	menu->releaseInstance();
	game->releaseInstance();

	graphics::destroyWindow();

	return EXIT_SUCCESS;
}