#pragma once
#include <Windows.h>
#include "Error.h"
#include <SFML\Graphics.hpp>
#include "Common.h"

using namespace sf;

class ErrorFile: public Error
{
public:
	RenderWindow* window;
	ErrorFile(RenderWindow* win) : window(win) {}

	virtual void error()
	{
		Text game_over("PROBLEM WITH FILE...", font, 60);
		game_over.setPosition(windowWidth / 2 - game_over.getGlobalBounds().width / 2,
			windowHeight / 2 - game_over.getGlobalBounds().height / 2);
		game_over.setFillColor(Color::White);
		window->clear(Color::Blue);
		window->draw(game_over);
		window->display();
		Sleep(5000);
		exit(0);
	}
};