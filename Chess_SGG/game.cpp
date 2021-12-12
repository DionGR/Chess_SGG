#include "game.h"
#include "graphics.h"

Game::Game()
{
	if (graphics::getGlobalTime() > 2000) {
		player = new Player();
	}
}

Game::~Game()
{
	if (player)
		delete player;
}

void Game::update()
{
}

void Game::draw()
{
}

void Game::init()
{
}
