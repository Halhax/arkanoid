#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>

using namespace std;
using namespace sf;

const float windowWidth = 800;
const float windowHeight = 600;
const int numberOfLevels = 3;

class Game
{
public:
	enum GameState { MENU, NEWGAME, OPTIONS, END };
	GameState position;

	Game();
	~Game();

	void runGame();
	void openFile();

protected:

	Font font;
	fstream file;
	Music music;

private:

	void play();
	void menu();
	void options();
	
};

