#include "Level.h"
#include "Ball.h"
#include "Paddle.h"
#include <Windows.h>
#include "TestCollision.h"

using namespace sf;

int Level::points(0);
int Level::lifes(numberOfLifes);

Level::Level() {}

Level::Level(RenderWindow *win) : window(win) {}

GameState Level::runEngine(int currentLevel)
{
	createBricks(currentLevel);

	Ball ball(windowWidth / 2, windowHeight / 2);
	Paddle paddle(windowWidth / 2, windowHeight - 50);
	
	Text textBoxPoints("POINTS: ", font, 20);
	textBoxPoints.setPosition(20, 565);
	textBoxPoints.setFillColor(Color::Black);

	Text textPoints;
	textPoints.setCharacterSize(20);
	textPoints.setFillColor(Color::Black);
	textPoints.setPosition(110, 565);
	textPoints.setFont(font);

	Text textBoxLives("LIVES: ", font, 20);
	textBoxLives.setPosition(700, 565);
	textBoxLives.setFillColor(Color::Black);

	Text textLives;
	textLives.setCharacterSize(20);
	textLives.setFillColor(Color::Black);
	textLives.setPosition(770, 565);
	textLives.setFont(font);

	Text level_num("Level: " + to_string(currentLevel), font, 60);
	level_num.setPosition(windowWidth / 2 - level_num.getGlobalBounds().width / 2,
		windowHeight / 2 - level_num.getGlobalBounds().height / 2);
	level_num.setFillColor(Color::Black);
	window->clear(Color::White);
	window->draw(level_num);
	window->display();
	Sleep(2000);

	Event event;

	gameState = NEWGAME;

	while (gameState == NEWGAME)
	{
		window->pollEvent(event);

		if (event.key.code == Keyboard::Escape) {
			gameState = MENU;
			return gameState;
		}

		if (event.type == Event::Closed)
			exit(0);

		if (ball.update() == true)
		{
			--lifes;

			if (!alive())
			{
				Text game_over("GAME OVER", font, 60);
				game_over.setPosition(windowWidth / 2 - game_over.getGlobalBounds().width / 2,
					windowHeight / 2 - game_over.getGlobalBounds().height / 2);
				textPoints.setPosition(windowWidth / 2 - game_over.getGlobalBounds().width / 2 + 240,
					windowHeight / 2 - game_over.getGlobalBounds().height / 2 + 80);
				textBoxPoints.setPosition(windowWidth / 2 - game_over.getGlobalBounds().width / 2 + 110,
					windowHeight / 2 - game_over.getGlobalBounds().height / 2 + 80);
				textPoints.setCharacterSize(30);
				textBoxPoints.setCharacterSize(30);
				game_over.setFillColor(Color::Black);
				window->clear(Color::White);
				window->draw(game_over);
				window->draw(textPoints);
				window->draw(textBoxPoints);
				window->display();
				Sleep(4000);
				gameState = MENU;
				return gameState;
			}
		}

		paddle.update();
		testCollision(paddle, ball);

		window->setFramerateLimit(60);
		window->clear(Color::White);

		window->draw(ball.ballShape);
		window->draw(paddle.paddleShape);

		textLives.setString(to_string(lifes));
		window->draw(textLives);
		window->draw(textBoxLives);

		textPoints.setString(to_string(points));
		window->draw(textPoints);
		window->draw(textBoxPoints);

		for (auto& brick : bricks)
		{
			window->draw(brick.brickShape);
			if (testCollision(brick, ball) == true)
				points++;
		}

		// algoritm STL - cool C++11 lambda!
		bricks.erase(remove_if(bricks.begin(), bricks.end(), [](const Brick& mBrick) { return mBrick.destroyed; }), bricks.end());

		if (bricks.empty() == true)
		{
			if (currentLevel == numberOfLevels) {
				Text game_over("YOU WIN !", font, 60);
				game_over.setPosition(windowWidth / 2 - game_over.getGlobalBounds().width / 2,
					windowHeight / 2 - game_over.getGlobalBounds().height / 2);
				textPoints.setPosition(windowWidth / 2 - game_over.getGlobalBounds().width / 2 + 230,
					windowHeight / 2 - game_over.getGlobalBounds().height / 2 + 80);
				textBoxPoints.setPosition(windowWidth / 2 - game_over.getGlobalBounds().width / 2 + 90,
					windowHeight / 2 - game_over.getGlobalBounds().height / 2 + 80);
				textPoints.setCharacterSize(30);
				textBoxPoints.setCharacterSize(30);
				game_over.setFillColor(Color::Black);
				window->clear(Color::White);
				window->draw(game_over);
				window->draw(textPoints);
				window->draw(textBoxPoints);
				window->display();
				Sleep(4000);
				gameState = MENU;
				return gameState;
			}

			Text level_num("Level: " + to_string(currentLevel + 1), font, 60);
			level_num.setPosition(windowWidth / 2 - level_num.getGlobalBounds().width / 2,
				windowHeight / 2 - level_num.getGlobalBounds().height / 2);
			level_num.setFillColor(Color::Black);
			window->clear(Color::White);
			window->draw(level_num);
			window->display();
			Sleep(2000);
			break;
		}
		window->display();
	}
	gameState = NEWGAME;
	return gameState;
}

void Level::createBricks(int countLevel) {}

Level::~Level() {
	lifes = numberOfLifes;
	points = 0;
}