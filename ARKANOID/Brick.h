#pragma once

#include <SFML\Graphics.hpp>

using namespace sf;

const float blockWidth = 60;
const float blockHeight = 20;

class Brick
{
public:
	RectangleShape brickShape;
	bool destroyed = false;

	Brick(float mX, float mY)
	{
		brickShape.setPosition(mX, mY);
		brickShape.setSize({ blockWidth, blockHeight });
		brickShape.setFillColor(Color::Yellow);
		brickShape.setOrigin(blockWidth / 2, blockHeight / 2);
	}

	float x() { return brickShape.getPosition().x; }
	float y() { return brickShape.getPosition().y; }
	float left() { return x() - brickShape.getSize().x / 2; }
	float right() { return x() + brickShape.getSize().x / 2; }
	float top() { return y() - brickShape.getSize().y / 2; }
	float bottom() { return y() + brickShape.getSize().y / 2; }
};