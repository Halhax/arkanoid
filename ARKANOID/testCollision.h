#pragma once
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"
#include <SFML/Graphics.hpp>

using namespace sf;

template<class T1, class T2> bool isIntersecting(T1& mA, T2& mB);

void testCollision(Paddle& mPaddle, Ball& mBall);

bool testCollision(Brick& mBrick, Ball& mBall);
