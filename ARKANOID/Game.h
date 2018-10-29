#pragma once

#include "Menu.h"
#include <SFML/Graphics.hpp>
#include "Common.h"
#include "GameState.h"

using namespace sf;

class Game
{
public:
	RenderWindow* window = new RenderWindow(VideoMode(windowWidth, windowHeight), "ARKANOID 1.3 (beta)", Style::Default, sf::ContextSettings());
	Menu* menu = new Menu(window);
	GameState gameState;

	Game();
	~Game();

	void run();
};