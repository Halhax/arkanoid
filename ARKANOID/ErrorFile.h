#pragma once
#include "Error.h"
#include "Game.h"
#include <Windows.h>

class ErrorFile: protected Game, public Error
{
public:

	virtual void error()
	{
		RenderWindow window(VideoMode(800, 600), "ERROR !");
	
		Text game_over("PROBLEM WITH FILE...", font, 60);
		game_over.setPosition(windowWidth / 2 - game_over.getGlobalBounds().width / 2,
			windowHeight / 2 - game_over.getGlobalBounds().height / 2);
		game_over.setColor(Color::White);
		window.clear(Color::Blue);
		window.draw(game_over);
		window.display();
		Sleep(5000);
		exit(0);
		
	}
};