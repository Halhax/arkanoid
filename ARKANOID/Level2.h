#pragma once

#include <SFML/Graphics.hpp>
#include "Level.h"

class Level2 :public Level
{
public:

	Level2(RenderWindow& win, GameState& state);
	~Level2(void);
	
	void create();

};