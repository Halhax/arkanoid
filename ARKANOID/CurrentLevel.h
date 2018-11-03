#pragma once

#include <SFML/Graphics.hpp>
#include "Level.h"

using namespace std;
using namespace sf;

class CurrentLevel : public Level
{
	void createBricks();
public:
	GameState run();
	CurrentLevel();
	CurrentLevel(shared_ptr<RenderWindow> win, int currentLevel);
};