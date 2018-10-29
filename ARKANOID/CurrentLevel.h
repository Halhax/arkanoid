#pragma once

#include <SFML/Graphics.hpp>
#include "Level.h"

using namespace sf;

class CurrentLevel : public Level
{
public:
	CurrentLevel();
	CurrentLevel(RenderWindow* win);
	~CurrentLevel();

	void createBricks(int countLevel);
};