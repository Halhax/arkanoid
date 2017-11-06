#include <Windows.h>
#include <fstream>
#include <iostream>

#include "CurrentLevel.h"
#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"
#include "testCollision.h"

using namespace std;
using namespace sf;

CurrentLevel::CurrentLevel(RenderWindow& win, GameState & st) : Level(win, st) {
}

CurrentLevel::~CurrentLevel(void)
{
}

void CurrentLevel::create(int countLevel)
{

	points = 0;
	cout << countLevel;
	
	fstream file;
	
	file.open("data/pattern" + to_string(countLevel) + ".txt");

	if (!file.good())
	{
		system("pause");
		exit(0);
	}

	string lol;
	for (int iY = 0; iY < countBlocksY; iY++)
	{
		getline(file, lol);
		for (int iX = 0; iX < countBlocksX; iX++)
		{
			if (lol[iX] == '+')
				bricks.emplace_back((iX + 1) * (blockWidth + 3) + 22, (iY + 2) * (blockHeight + 3));

		}
	}
}