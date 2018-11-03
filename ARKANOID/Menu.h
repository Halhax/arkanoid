#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <iostream>
#include "GameState.h"
#include "Common.h"

using namespace sf;
using namespace std;

class Menu
{
	bool musicStatus;
	shared_ptr<RenderWindow> window;
	SoundSource::Status actualMusicStatus;
	Music music;
	GameState gameState;
	fstream configFile;
	void loadConfigFile();

public:
	static int controlMouse;
	Menu();
	Menu(shared_ptr<RenderWindow> win);

	GameState menu();
	GameState play();
	GameState options();
};