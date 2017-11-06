#pragma once
#include "Error.h"
#include "Game.h"
#include <Windows.h>

class ErrorMusic : protected Game, public Error
{
public:

	virtual void error()
	{
		RenderWindow window(VideoMode(800, 600), "ERROR !");

		Text game_over("BLAD MUZYKI", font, 60);
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