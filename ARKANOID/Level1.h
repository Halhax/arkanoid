#pragma once

#include <SFML/Graphics.hpp>
#include "Level.h"

using namespace sf;

class Level1: public Level
{
public:
	
	Level1(RenderWindow& win, GameState& state);
	~Level1(void);
	
	void create();
	
};

