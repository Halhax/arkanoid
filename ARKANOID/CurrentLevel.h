#pragma once

#include <SFML/Graphics.hpp>
#include "Level.h"

using namespace sf;

class CurrentLevel : public Level
{
public:

	CurrentLevel(RenderWindow& win, GameState& state);
	~CurrentLevel(void);

	void create(int countLevel);

};

