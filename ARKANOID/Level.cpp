#include <Windows.h>
#include "SFML/Audio.hpp"
#include "Level.h"
#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"
#include "testCollision.h"
#include <fstream>
#include <iostream>

using namespace std;
using namespace sf;

int Level::points(0);

Level::Level(RenderWindow & win, GameState & st):window(win), state(st) {

	
}

Level::~Level(void)
{
}

void Level::create(int countLevel)
{
}

void Level::runEngine(int countLevel)
{
	create(countLevel);

	window.setFramerateLimit(60);

	Ball ball(windowWidth / 2, windowHeight / 2);
	Paddle paddle(windowWidth / 2, windowHeight - 50);
	
	Text statistic("POINTS: ", font, 20);
	statistic.setPosition(20, 565);
	statistic.setColor(Color::Black);

	Text point;
	point.setCharacterSize(20);
	point.setColor(Color::Black);
	point.setPosition(110, 565);
	point.setFont(font);

	Text lives("LIVES: ", font, 20);
	lives.setPosition(700, 565);
	lives.setColor(Color::Black);

	Text live;
	live.setCharacterSize(20);
	live.setColor(Color::Black);
	live.setPosition(770, 565);
	live.setFont(font);

	Event event;

	while (state == NEWGAME)
	{
		window.pollEvent(event);

		if (event.key.code == Keyboard::Escape)
			state = MENU;

		if (event.type == Event::Closed)
			exit(0);

		if (ball.update() == true)
		{
			--ball;

			if (!ball.alive())
			{
				Text game_over("GAME OVER", font, 60);
				game_over.setPosition(windowWidth / 2 - game_over.getGlobalBounds().width / 2,
					windowHeight / 2 - game_over.getGlobalBounds().height / 2);
				game_over.setColor(Color::Black);
				window.clear(Color::White);
				window.draw(game_over);
				window.display();
				Sleep(2000);
				state = MENU;
			}
		}

		paddle.update();
		testCollision(paddle, ball);

		window.clear(Color::White);

		window.draw(ball.shape);
		window.draw(paddle.shape);

		live.setString(to_string(ball.getLifes()));
		window.draw(live);
		window.draw(lives);

		point.setString(to_string(points));
		window.draw(point);
		window.draw(statistic);

		// for (int i = 0; i < bricks.size(); i++) window.draw(bricks[i].shape);

		for (auto& brick : bricks)
		{
			window.draw(brick.shape);
			if (testCollision(brick, ball) == true)
				points++;
		}
		// algoritm STL
		// cool C++11 lambda!

		bricks.erase(remove_if(begin(bricks), end(bricks), [](const Brick& mBrick) { return mBrick.destroyed; }), end(bricks));

		if (bricks.empty() == true)
		{
			Text game_over("YOU WIN !", font, 60);
			game_over.setPosition(windowWidth / 2 - game_over.getGlobalBounds().width / 2,
				windowHeight / 2 - game_over.getGlobalBounds().height / 2);
			game_over.setColor(Color::Black);
			window.clear(Color::White);
			window.draw(game_over);
			window.display();
			Sleep(2000);
			
			break;
		}

		window.display();
	}
}
