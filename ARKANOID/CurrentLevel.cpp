#include <fstream>
#include <string>
#include <Windows.h>
#include "CurrentLevel.h"

using namespace std;
using namespace sf;

CurrentLevel::CurrentLevel() {}

CurrentLevel::CurrentLevel(RenderWindow* win) : Level(win) {}

CurrentLevel::~CurrentLevel() {}

void CurrentLevel::createBricks(int countLevel)
{
	string line;
	fstream patternFile;
	
	patternFile.open("data/pattern" + to_string(countLevel) + ".txt");

	if (!patternFile.good())
	{
		MessageBox(window->getSystemHandle(), (LPCWSTR)L"Pattern file not found!", (LPCWSTR)L"ERROR! - missing element", MB_ICONERROR | MB_OKCANCEL);
		exit(0);
	}

	for (int iY = 0; iY < countBlocksY; iY++)
	{
		getline(patternFile, line);
		for (int iX = 0; iX < countBlocksX; iX++)
			if (line[iX] == '+')
				bricks.emplace_back((iX + 1) * (blockWidth + 3) + 22, (iY + 2) * (blockHeight + 3));
	}
}