#pragma once
using namespace sf;

const float blockWidth = 60;
const float blockHeight = 20;

const int countBlocksX = 11;
const int countBlocksY = 7;

class Brick
{
public:

	RectangleShape shape;

	// variable to checking if brick was destroyed
	bool destroyed = false;

	Brick(float mX, float mY)
	{
		shape.setPosition(mX, mY);
		shape.setSize({ blockWidth, blockHeight });
		shape.setFillColor(Color::Yellow);
		shape.setOrigin(blockWidth / 2, blockHeight / 2);
	}

	float x() { return shape.getPosition().x; }
	float y() { return shape.getPosition().y; }
	float left() { return x() - shape.getSize().x / 2; }
	float right() { return x() + shape.getSize().x / 2; }
	float top() { return y() - shape.getSize().y / 2; }
	float bottom() { return y() + shape.getSize().y / 2; }
};