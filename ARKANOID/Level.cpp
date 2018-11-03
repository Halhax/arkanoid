#include "Level.h"
#include "Ball.h"
#include "Paddle.h"
#include <Windows.h>
#include "TestCollision.h"
#include <iostream>

int Level::points(0);
int Level::lifes(numberOfLifes);

Level::Level() {}

Level::Level(shared_ptr<RenderWindow> win, int currLevel) : window(win), currentLevel(currLevel) {

	paddle = Paddle(windowWidth / 2, windowHeight - 50);
	ball = Ball(windowWidth / 2, windowHeight / 2);

	textBoxPoints.setString("POINTS: ");
	textBoxPoints.setFont(font);
	textBoxPoints.setCharacterSize(20);
	textBoxPoints.setPosition(20, 565);
	textBoxPoints.setFillColor(Color::Black);

	textPoints.setCharacterSize(20);
	textPoints.setFillColor(Color::Black);
	textPoints.setPosition(110, 565);
	textPoints.setFont(font);

	textBoxLives.setString("LIVES: ");
	textBoxLives.setFont(font);
	textBoxLives.setCharacterSize(20);
	textBoxLives.setPosition(700, 565);
	textBoxLives.setFillColor(Color::Black);

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
	Sleep(1000);

	gameState = NEWGAME;
}

float getFPS(const sf::Time& time) {
	return (1000000.0f / time.asMicroseconds());
}

GameState Level::runEngine()
{
	while (gameState == NEWGAME)
	{
		window->clear(Color::White);
		window->setFramerateLimit(60);
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
				drawGameOver();
				gameState = MENU;
				return gameState;
			}
		}
		drawElements();

		bricks.erase(remove_if(bricks.begin(), bricks.end(), [](const Brick& mBrick) { return mBrick.destroyed; }), bricks.end());
		
		paddle.update();
		testCollision(paddle, ball);

		if (bricks.empty() == true)
		{
			if (currentLevel == numberOfLevels) {
				drawLevelEnd();
				gameState = MENU;
				return gameState;
			}
			drawLevelInfo();
			break;
		}
		window->display();
		//float fps = getFPS(FPSClock.restart());
	}
	gameState = NEWGAME;
	return gameState;
}

void Level::drawGameOver() {
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
}
void Level::drawLevelInfo() {
	Text level_num("Level: " + to_string(currentLevel + 1), font, 60);
	level_num.setPosition(windowWidth / 2 - level_num.getGlobalBounds().width / 2,
		windowHeight / 2 - level_num.getGlobalBounds().height / 2);
	level_num.setFillColor(Color::Black);
	window->clear(Color::White);
	window->draw(level_num);
	window->display();
}
void Level::drawLevelEnd() {
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
}
void Level::drawElements() {
	window->draw(ball.ballShape);
	window->draw(paddle.paddleShape);

	for (auto& brick : bricks)
	{
		window->draw(brick.brickShape);
		if (testCollision(brick, ball) == true)
			points++;
	}

	textLives.setString(to_string(lifes));
	window->draw(textLives);

	textPoints.setString(to_string(points));
	window->draw(textPoints);

	window->draw(textBoxLives);
	window->draw(textBoxPoints);
}

Level::~Level() {
	lifes = numberOfLifes;
	points = 0;
}