#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"
using namespace sf;

class Paddle
{
public:
	RectangleShape shape;
	Vector2f velocity;

	const float paddleWidth = 150;
	const float paddleHeight = 20;
	const float paddleVelocity =1;

	Paddle(float mX, float mY)
	{
		shape.setPosition(mX, mY);
		shape.setSize(Vector2f( paddleWidth , paddleHeight ));
		//shape.setSize({ paddleWidth , paddleHeight });
		shape.setFillColor(Color::Black);
		shape.setOrigin(paddleWidth / 2, paddleHeight / 2);
	}

	void update()
	{
		shape.move(velocity);

		if (Keyboard::isKeyPressed(Keyboard::Key::Left) && left() > 0)
			velocity.x = -paddleVelocity;
		else if (Keyboard::isKeyPressed(Keyboard::Key::Right) && right() < windowWidth)
			velocity.x = paddleVelocity;
		else
			velocity.x = 0;
	}

	float x() { return shape.getPosition().x; }
	float y() { return shape.getPosition().y; }
	float left() { return x() - shape.getSize().x / 2; }
	float right() { return x() + shape.getSize().x / 2; }
	float top() { return y() - shape.getSize().y / 2; }
	float bottom() { return y() + shape.getSize().y / 2; }
};