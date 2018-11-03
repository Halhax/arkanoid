#pragma once

#include <vector>
#include "Brick.h"
#include "Ball.h"
#include "Paddle.h"
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "Common.h"

//using namespace sf;
using namespace std;

class Level
{
	static int points;
	static int lifes;
	GameState gameState;
	Ball ball;
	Paddle paddle;
	Text textLives;
	Text textPoints;
	Text textBoxPoints;
	Text textBoxLives;
	Event event;
	//Clock FPSClock;

	bool alive() const { return lifes > 0; }
	void drawGameOver();
	void drawLevelInfo();
	void drawLevelEnd();
	void drawElements();

public:
	Level();
	Level(shared_ptr<RenderWindow> win, int currLevel);
	virtual ~Level();

	virtual GameState run() = 0;

protected:
	vector<Brick> bricks;
	shared_ptr<RenderWindow> window;
	int currentLevel;
	virtual void createBricks() = 0;
	GameState runEngine();
};