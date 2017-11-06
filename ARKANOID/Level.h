#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "Brick.h"
#include "Game.h"

using namespace sf;

class Level :protected Game
{
public:
	static int points;
	
	vector<Brick> bricks;
	RenderWindow &window;
	GameState &state;

	Level(RenderWindow& win, GameState & st);
	~Level(void);
	
	virtual void create(int countLevel);
	virtual void runEngine(int countLevel);

};
