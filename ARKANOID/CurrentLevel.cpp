#include <fstream>
#include <string>
#include <Windows.h>
#include "CurrentLevel.h"

using namespace sf;
GameState CurrentLevel::run() {
	createBricks();
	return runEngine();
}

void CurrentLevel::createBricks()
{
	string line;
	fstream patternFile;

	patternFile.open("data/pattern" + to_string(currentLevel) + ".txt");

	if (!patternFile.good())
	{
		MessageBox(window->getSystemHandle(), (LPCWSTR)L"Pattern file not found!", (LPCWSTR)L"ERROR! - missing element", MB_ICONERROR | MB_OKCANCEL);
		return;
	}

	for (int iY = 0; iY < countBlocksY; iY++)
	{
		getline(patternFile, line);
		for (int iX = 0; iX < countBlocksX; iX++)
			if (line[iX] == '+')
				bricks.emplace_back((iX + 1) * (blockWidth + 3) + 22, (iY + 2) * (blockHeight + 3));
	}
}

CurrentLevel::CurrentLevel() {}

CurrentLevel::CurrentLevel(shared_ptr<RenderWindow> win, int currentLevel) : Level(win, currentLevel) {
	this->currentLevel = currentLevel;
}

