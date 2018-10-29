#pragma once

#include <vector>
#include "Brick.h"
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "Common.h"

using namespace sf;
using namespace std;

class Level
{
public:
	static int points;
	static int lifes;
	
	vector<Brick> bricks;
	RenderWindow* window;
	GameState gameState;
	
	Level();
	Level(RenderWindow* win);
	virtual ~Level();

	GameState runEngine(int countLevel);
	bool alive() const { return lifes > 0; }
	virtual void createBricks(int countLevel);
};