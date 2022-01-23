#include "debug.h"

#include "menu.h"
#include "game.h"

/**
* Chess v1.3
* author: Dionysios Rigatos (P3200262)
* 
* Made for AUEB - Department of Informatics' C++ Fall/Winter Semester Course -
* using Simple Game Library for the purposes of the lecture. 
* 
* VIDEO PRESENTATION: https://www.youtube.com/watch?v=NdRCUJB6Fl8
* 
* VERSIONS:
* v1.0 - Silverman 4x5 chessboard with limited pieces (First version worthy of being delivered as an assignment)
* v1.1 - Transition to full-scale 8x8 chessboard with all the pieces, castling & two-step pawn move
* v1.2 - Game Review Screen & Ability to retire early
* v1.3 - Captured piece icons & Stalemate
* NEXT: Simulation for check-mate checking, MULTIPLAYER(?)
* 
* 
* Credit for the assets go to their respective creators:
*	Assets/Sound Effects: Chess.com © 2022
*	Main Menu Music: Local Forecast - Slower © 2013 Kevin MacLeod
*/

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
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);

	Menu* menu{ Menu::getInstance() };
	Game* game{ Game::getInstance() };

	graphics::createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME);
	graphics::setCanvasSize(CANVAS_WIDTH, CANVAS_WIDTH);
	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

	menu->init();

	graphics::setUserData(game);
	graphics::setDrawFunction(draw);
	graphics::setUpdateFunction(update);
	graphics::startMessageLoop();

	menu->releaseInstance();
	game->releaseInstance();

	graphics::destroyWindow();

	_CrtDumpMemoryLeaks();

	return EXIT_SUCCESS;
}
