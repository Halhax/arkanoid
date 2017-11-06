#pragma once

#include "Game.h"

using namespace sf;

const float ballRadius = 10;
const float ballVelocity = 8;

class Ball
{
public:

	CircleShape shape;
	Vector2f velocity{ 0, ballVelocity };

	Ball(float mX, float mY):lifes(3)
	{
		shape.setPosition(mX, mY);
		shape.setRadius(ballRadius);
		shape.setFillColor(Color::Red);
		shape.setOrigin(ballRadius, ballRadius);
	}

	bool update()
	{
		shape.move(velocity);

		if (left() < 0)
			velocity.x = ballVelocity;
		else if (right() > windowWidth)
			velocity.x = -ballVelocity;

		if (top() < 0)
			velocity.y = ballVelocity;
		else if (bottom() > windowHeight)
		{
			velocity.x = 0;
			velocity.y = ballVelocity / 2;
			shape.setPosition(windowWidth / 2, windowHeight / 2);
			return true;
		}
			
		return false;
	}

	float x() { return shape.getPosition().x; }
	float y() { return shape.getPosition().y; }
	float left() { return x() - shape.getRadius(); }
	float right() { return x() + shape.getRadius(); }
	float top() { return y() - shape.getRadius(); }
	float bottom() { return y() + shape.getRadius(); }

	Ball& operator-- () { lifes--; return *this; }

	bool alive() const { return lifes > 0; }
	int getLifes() const { return lifes; }

protected:
	int lifes;

};