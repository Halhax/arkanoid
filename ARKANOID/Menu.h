#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <iostream>
#include "GameState.h"
#include "Common.h"

using namespace sf;

class Menu
{
public:
	bool musicStatus;
	RenderWindow* window;
	SoundSource::Status actualMusicStatus;
	Music music;
	GameState gameState;
	std::fstream configFile;
	
	Menu();
	Menu(RenderWindow* win);

	GameState menu();
	GameState play();
	GameState options();
	void loadConfigFile();
};