#include "Menu.h"
#include <Windows.h>
#include "Error.h"
#include "ErrorFile.h"
#include "Level.h"
#include "CurrentLevel.h"
#include "GameState.h"

Font font;

int Menu::controlMouse = false;

Menu::Menu() {}

Menu::Menu(std::shared_ptr<RenderWindow> win) : window(win) {

	if (!font.loadFromFile("data/JOKERMAN.TTF"))
	{
		MessageBox(window->getSystemHandle(), (LPCWSTR)L"Font not found!", (LPCWSTR)L"ERROR! - missing element", MB_ICONERROR | MB_OKCANCEL);
		exit(0);
	}
	if (!music.openFromFile("data/MusicForPlaying.ogg"))
	{
		MessageBox(window->getSystemHandle(), (LPCWSTR)L"Audio file not found!", (LPCWSTR)L"ERROR! - missing element", MB_ICONERROR | MB_OKCANCEL);
		exit(0);
	}

	loadConfigFile();

	gameState = MENU;
}

GameState Menu::menu()
{
	actualMusicStatus = music.getStatus();
	if (musicStatus && actualMusicStatus != SoundSource::Status::Playing)
		music.play();

	Text title("Arkanoid", font, 80);
	title.setStyle(Text::Bold);
	title.setPosition(800 / 2 - title.getGlobalBounds().width / 2, 40);

	const int count = 3;
	Text txt[count];

	string str[] = { "New Game", "Options", "Exit" };

	for (int i = 0; i < count; i++)
	{
		txt[i].setFont(font);
		txt[i].setCharacterSize(50);
		txt[i].setString(str[i]);
		txt[i].setPosition((float)800 / (float)2 - txt[i].getGlobalBounds().width / (float)2, (float)200 + i * (float)120);
	}

	Event event;
	while (gameState == MENU)
	{
		Vector2f mouse(Mouse::getPosition(*window));

		window->pollEvent(event);

		if (event.type == Event::Closed) {
			gameState = END;
			return END;
		}
			
		if (txt[0].getGlobalBounds().contains(mouse) &&
			event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
		{
			gameState = NEWGAME;
			return NEWGAME;
		}
		if (txt[1].getGlobalBounds().contains(mouse) &&
			event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
		{
			gameState = OPTIONS;
			return OPTIONS;
		}
		if (txt[2].getGlobalBounds().contains(mouse) &&
			event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
		{
			gameState = END;
			return END;
		}

		for (int i = 0; i < count; i++)
			if (txt[i].getGlobalBounds().contains(mouse))
				txt[i].setFillColor(Color::Cyan);
			else 
				txt[i].setFillColor(Color::White);

		window->clear();
		window->draw(title);
		for (int i = 0; i < count; i++)
			window->draw(txt[i]);
		window->display();
	}
	return MENU;
}

GameState Menu::options()
{
	Text title("Options", font, 80);
	title.setStyle(Text::Bold);
	title.setPosition(800 / 2 - title.getGlobalBounds().width / 2, 40);

	const int count = 2;

	Text txt1[count];
	Text txt2[count];
	Text txt3[count];
	string options[] = { "Control: ", "Music: " };
	string musicOptions[] = { "ON", "OFF" };
	string controlOptions[] = { "Mouse", "Keyboard" };

	for (int i = 0; i < count; i++)
	{
		txt1[i].setFont(font);
		txt1[i].setCharacterSize(40);
		txt1[i].setString(options[i]);
		txt1[i].setPosition((float)800 / (float)2 - txt1[i].getGlobalBounds().width / (float)2 - 200, (float)200 + i * (float)120 + 10);
		txt1[i].setFillColor(Color::White);

		txt2[i].setFont(font);
		txt2[i].setCharacterSize(40);
		txt2[i].setString(musicOptions[i]);
		txt2[i].setPosition((float)800 / (float)2 + txt1[i].getGlobalBounds().width / (float)2 + i * (float)120 - 80, (float)200 + (float)120 + 10);
		txt2[i].setFillColor(Color::White);

		txt3[i].setFont(font);
		txt3[i].setCharacterSize(40);
		txt3[i].setString(controlOptions[i]);
		txt3[i].setPosition((float)800 / (float)2 + txt3[i].getGlobalBounds().width / (float)2 + i * (float)120 - 140, (float)200 + 10);
		txt3[i].setFillColor(Color::White);
	}

	if (musicStatus) {
		txt2[0].setFillColor(Color::Cyan);
		txt2[1].setFillColor(Color::White);
	}
	else {
		txt2[0].setFillColor(Color::White);
		txt2[1].setFillColor(Color::Cyan);
	}

	if (controlMouse) {
		txt3[0].setFillColor(Color::Cyan);
		txt3[1].setFillColor(Color::White);
	}
	else {
		txt3[0].setFillColor(Color::White);
		txt3[1].setFillColor(Color::Cyan);
	}

	Event event;

	while (gameState == OPTIONS)
	{
		Vector2f mouse(Mouse::getPosition(*window));

		window->pollEvent(event);
		if (event.type == Event::Closed || event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
			gameState = MENU;
			break;
		}
			
		if (txt2[0].getGlobalBounds().contains(mouse) &&
			event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left)
		{
			music.play();
			configFile.open("data/musicStateSave.txt", ios::out);
			configFile << '1';
			configFile.close();
			txt2[0].setFillColor(Color::Cyan);
			txt2[1].setFillColor(Color::White);
		}

		else if (txt2[1].getGlobalBounds().contains(mouse) &&
			event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left)
		{
			music.pause();
			configFile.open("data/musicStateSave.txt", ios::out);
			configFile << '0';
			configFile.close();
			musicStatus = 0;
			txt2[0].setFillColor(Color::White);
			txt2[1].setFillColor(Color::Cyan);
		}
		if (txt3[0].getGlobalBounds().contains(mouse) &&
			event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left)
		{
			configFile.open("data/controlMouse.txt", ios::out);
			configFile << '1';
			configFile.close();
			controlMouse = true;
			txt3[0].setFillColor(Color::Cyan);
			txt3[1].setFillColor(Color::White);
		}

		else if (txt3[1].getGlobalBounds().contains(mouse) &&
			event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left)
		{
			configFile.open("data/controlMouse.txt", ios::out);
			configFile << '0';
			configFile.close();
			controlMouse = false;
			txt3[0].setFillColor(Color::White);
			txt3[1].setFillColor(Color::Cyan);
		}

		window->clear();

		for (int i = 0; i < count; i++) {
			window->draw(txt1[i]);
			window->draw(txt2[i]);
			window->draw(txt3[i]);
		}

		window->draw(title);
		window->display();
	}
	return gameState;
}

void Menu::loadConfigFile()
{
	unique_ptr<Error> ptr = make_unique<ErrorFile>(window);
	
	configFile.open("data/musicStateSave.txt");
	if (!configFile.good())
		ptr->error();

	configFile >> musicStatus;
	configFile.close();

	configFile.open("data/controlMouse.txt");
	if (!configFile.good())
		ptr->error();

	configFile >> controlMouse;
	configFile.close();
}

GameState Menu::play()
{
	Level* level;
	for (int i = 1; i <= numberOfLevels; i++)
	{
		level = new CurrentLevel(window, i);
		gameState = level->run();
		if(gameState == MENU)
			break;
	}
	delete level;
	gameState = MENU;
	return gameState;
}