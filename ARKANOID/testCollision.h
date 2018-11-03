#pragma once

#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"

template<class T1, class T2>
bool isIntersecting(T1& mA, T2& mB)
{
	if (mA.right() >= mB.left() && mA.left() <= mB.right()
		&& mA.bottom() >= mB.top() && mA.top() <= mB.bottom())
		return 1;
	else
		return 0;
}

void testCollision(Paddle& mPaddle, Ball& mBall)
{
	if (!isIntersecting(mPaddle, mBall)) return;

	mBall.ballVelocity.y = -constBallVelocity;

	if (mBall.x() < mPaddle.x() + 1 && mBall.x() > mPaddle.x() - 1)
	{
		mBall.ballVelocity.x = 0;
	}
	else if (mBall.x() < mPaddle.x()) {
		if (mBall.x() < mPaddle.x() - 35) {
			mBall.ballVelocity.x = -constBallVelocity;
		}
		else if (mBall.x() < mPaddle.x() - 20) {
			mBall.ballVelocity.x = -(constBallVelocity / 2);
		}
		else if (mBall.x() < mPaddle.x() - 10) {
			mBall.ballVelocity.x = -(constBallVelocity / 3);
		}
		else if (mBall.x() < mPaddle.x() - 1) {
			mBall.ballVelocity.x = -(constBallVelocity / 4);
		}
	}
	else {
		if (mBall.x() > mPaddle.x() + 35) {
			mBall.ballVelocity.x = constBallVelocity;;
		}
		else if (mBall.x() > mPaddle.x() + 20) {
			mBall.ballVelocity.x = (constBallVelocity / 2);
		}
		else if (mBall.x() > mPaddle.x() + 10) {
			mBall.ballVelocity.x = (constBallVelocity / 3);
		}
		else if (mBall.x() > mPaddle.x() + 1) {
			mBall.ballVelocity.x = (constBallVelocity / 4);
		}
	}
}

bool testCollision(Brick& mBrick, Ball& mBall)
{
	if (!isIntersecting(mBrick, mBall))
		return false;
	else {
		mBrick.destroyed = true;

		float overlapLeft(mBall.right() - mBrick.left());
		float overlapRight(mBrick.right() - mBall.left());
		float overlapTop(mBall.bottom() - mBrick.top());
		float overlapBottom(mBrick.bottom() - mBall.top());

		bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));
		bool ballFromTop(abs(overlapTop) < abs(overlapBottom));

		float minOverlapX{ ballFromLeft ? overlapLeft : overlapRight };
		float minOverlapY{ ballFromTop ? overlapTop : overlapBottom };

		if (abs(minOverlapX) < abs(minOverlapY))
			mBall.ballVelocity.x = ballFromLeft ? -constBallVelocity : constBallVelocity;
		else
			mBall.ballVelocity.y = ballFromTop ? -constBallVelocity : constBallVelocity;

		return true;
	}
}