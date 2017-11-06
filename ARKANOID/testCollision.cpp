#include "testCollision.h"

template<class T1, class T2> bool isIntersecting(T1& mA, T2& mB)
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

	mBall.velocity.y = -ballVelocity;

	if (mBall.x() < mPaddle.x() + 25 && mBall.x() > mPaddle.x() - 25)
	{
		mBall.velocity.x = 0;
		mBall.velocity.y = -ballVelocity;
	}
	else if (mBall.x() < mPaddle.x())
		mBall.velocity.x = -ballVelocity;
	else
		mBall.velocity.x = ballVelocity;
}

bool testCollision(Brick& mBrick, Ball& mBall)
{

	if (!isIntersecting(mBrick, mBall)) return false;

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
		mBall.velocity.x = ballFromLeft ? -ballVelocity : ballVelocity;
	else
		mBall.velocity.y = ballFromTop ? -ballVelocity : ballVelocity;

	return true;
}