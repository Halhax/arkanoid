#include <Windows.h>
#include <fstream>
#include <iostream>

#include "SFML/Audio.hpp"
#include "Level2.h"
#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"
#include "testCollision.h"

Level2::Level2(RenderWindow& win, GameState & st) : Level(win, st) {

	//state = NEWGAME;
}

Level2::~Level2(void)
{
}

void Level2::create()
{

	fstream file;
	file.open("data/pattern2.txt");
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