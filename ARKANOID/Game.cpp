#include "Game.h"
#include "Common.h"

Game::Game()
{
	gameState = MENU;
}

void Game::run()
{
	while (gameState != END)
	{
		switch (gameState)
		{
		case MENU:
			gameState = menu->menu();
			break;
		case NEWGAME:
			gameState = menu->play();
			break;
		case OPTIONS:
			gameState = menu->options();
			break;
		}
	}
}

Game::~Game() {
	delete window;
	delete menu;
}