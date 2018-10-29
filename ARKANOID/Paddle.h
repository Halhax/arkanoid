#pragma once

#include <SFML/Graphics.hpp>
#include "Common.h"

using namespace sf;

class Paddle
{
public:
	RectangleShape paddleShape;
	Vector2f paddleVelocity;

	const float paddleWidth = 150;
	const float paddleHeight = 20;
	const float constPaddleVelocity = 12;

	Paddle(float mX, float mY)
	{
		paddleShape.setPosition(mX, mY);
		paddleShape.setSize(Vector2f( paddleWidth , paddleHeight ));
		paddleShape.setFillColor(Color::Black);
		paddleShape.setOrigin(paddleWidth / 2, paddleHeight / 2);
	}

	void update()
	{
		paddleShape.move(paddleVelocity);

		if (Keyboard::isKeyPressed(Keyboard::Key::Left) && left() > 0)
			paddleVelocity.x = -constPaddleVelocity;
		else if (Keyboard::isKeyPressed(Keyboard::Key::Right) && right() < windowWidth)
			paddleVelocity.x = constPaddleVelocity;
		else
			paddleVelocity.x = 0;
	}

	float x() { return paddleShape.getPosition().x; }
	float y() { return paddleShape.getPosition().y; }
	float left() { return x() - paddleShape.getSize().x / 2; }
	float right() { return x() + paddleShape.getSize().x / 2; }
	float top() { return y() - paddleShape.getSize().y / 2; }
	float bottom() { return y() + paddleShape.getSize().y / 2; }
};