#pragma once

#include <SFML\Graphics.hpp>
#include "Common.h"

using namespace sf;

const float constBallVelocity = 6;
const float ballRadius = 10;

class Ball
{
public:

	CircleShape ballShape;
	Vector2f ballVelocity{ 0, constBallVelocity };

	Ball() {}
	Ball(float mX, float mY)
	{
		ballShape.setPosition(mX, mY);
		ballShape.setRadius(ballRadius);
		ballShape.setFillColor(Color::Red);
		ballShape.setOrigin(ballRadius, ballRadius);
	}

	bool update()
	{
		ballShape.move(ballVelocity);

		if (left() < 0)
			ballVelocity.x = constBallVelocity;
		else if (right() > windowWidth)
			ballVelocity.x = -constBallVelocity;

		if (top() < 0)
			ballVelocity.y = constBallVelocity;
		else if (bottom() > windowHeight)
		{
			ballVelocity.x = 0;
			ballVelocity.y = constBallVelocity / 2;
			ballShape.setPosition(windowWidth / 2, windowHeight / 2);
			return true;
		}
		return false;
	}

	float x() { return ballShape.getPosition().x; }
	float y() { return ballShape.getPosition().y; }
	float left() { return x() - ballShape.getRadius(); }
	float right() { return x() + ballShape.getRadius(); }
	float top() { return y() - ballShape.getRadius(); }
	float bottom() { return y() + ballShape.getRadius(); }
};