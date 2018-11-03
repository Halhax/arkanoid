#pragma once

#include "Menu.h"
#include <SFML/Graphics.hpp>
#include "Common.h"
#include "GameState.h"

using namespace std;
using namespace sf;

class Game
{
	shared_ptr<RenderWindow> window = make_shared<RenderWindow>(VideoMode(windowWidth, windowHeight), "ARKANOID 1.3 (beta)", Style::Default, sf::ContextSettings());
	unique_ptr<Menu> menu = make_unique<Menu>(window);
	GameState gameState;

public:
	Game();
	void run();
};