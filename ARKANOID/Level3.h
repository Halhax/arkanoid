#pragma once

#include <SFML/Graphics.hpp>
#include "Level.h"

class Level3 :public Level
{
public:

	Level3(RenderWindow& win, GameState& state);
	~Level3(void);

	void create();

};