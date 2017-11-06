#include "Game.h"
#include "CurrentLevel.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Error.h"
#include "ErrorFile.h"

#include <Windows.h>
#include <iostream>

RenderWindow window(VideoMode(800, 600), "ARKANOID 1.0 (beta)", Style::Default, sf::ContextSettings());// Style::Fullscreen);

Game::Game()
{

	position = END;

	if (!font.loadFromFile("data/JOKERMAN.TTF"))
	{
		//MessageBox(window.getSystemHandle(), "Nie znaleziono czcionki ! :C", "ERROR !", MB_OKCANCEL);
		return;
	}

	if (!music.openFromFile("data/MusicForPlaying.ogg"))
	{
		//MessageBox(window.getSystemHandle(), "Nie znaleziono dŸwiêku ! :C", "ERROR !", MB_OKCANCEL);
		return;
	}

	position = MENU;
}

Game::~Game()
{
}

void Game::runGame()
{
	position = MENU;

	while (position != END)
	{
		switch (position)
		{
		case GameState::MENU:
			menu();
			break;
		case GameState::NEWGAME:
			play();
			break;
		case GameState::OPTIONS:
			options();
			break;
		}
	}
}

void Game::menu()
{	
	bool check;

	openFile();
	
	file >> check;
	file.close();

	SoundSource::Status check2 = music.getStatus();

	if (check && check2!=SoundSource::Status::Playing)
		music.play();

	Text title("Arkanoid", font, 80);
	title.setStyle(Text::Bold);
	title.setPosition(800 / 2 - title.getGlobalBounds().width / 2, 20);

	const int count = 3;

	Text txt[count];
	string str[] = { "New Game", "Options", "Exit" };
	
	for (int i = 0; i<count; i++)
	{
		txt[i].setFont(font);
		txt[i].setCharacterSize(50);
		txt[i].setString(str[i]);
		txt[i].setPosition((float)800 / (float)2 - txt[i].getGlobalBounds().width / (float)2, (float)200 + i * (float)120);
	}

	Event event;
	while (position == MENU)
	{

		Vector2f mouse(Mouse::getPosition(window));
		
		
		window.pollEvent(event);
		
		if (event.type == Event::Closed )
			position = END;

		if (txt[0].getGlobalBounds().contains(mouse) && 
			event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
		{
			position = NEWGAME;
		}
		if (txt[1].getGlobalBounds().contains(mouse) &&
			event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
		{
			position = OPTIONS;
		}
		if (txt[2].getGlobalBounds().contains(mouse) &&
			event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
		{
			position = END;
		}

		for (int i = 0; i<count; i++)
			if (txt[i].getGlobalBounds().contains(mouse))
				txt[i].setColor(Color::Cyan);
			else txt[i].setColor(Color::White);

		window.clear();

		window.draw(title);
		for (int i = 0; i<count; i++)
			window.draw(txt[i]);

		window.display();
	}
}

void Game::options()
{
	Text title("Options", font, 80);
	title.setStyle(Text::Bold);
	title.setPosition(800 / 2 - title.getGlobalBounds().width / 2, 20);

	const int count = 2;

	Text txt1[count];
	Text txt2[count];
	string str[] = { "Control", "Music: " };
	string str1[] = { "ON", "OFF" };

	for (int i = 0; i<count; i++)
	{
		txt1[i].setFont(font);
		txt1[i].setCharacterSize(40);
		txt1[i].setString(str[i]);
		txt1[i].setPosition((float)800 / (float)2 - txt1[i].getGlobalBounds().width / (float)2, (float)200 + i * (float)120);
		txt1[i].setColor(Color::White);

		txt2[i].setFont(font);
		txt2[i].setCharacterSize(40);
		txt2[i].setString(str1[i]);
		txt2[i].setPosition((float)800 / (float)2 + txt1[i].getGlobalBounds().width / (float)2 + i * (float)120, (float)200 + (float)120);
		txt2[i].setColor(Color::White);
	}

	Event event;

	while (position == OPTIONS)
	{
		Vector2f mouse(Mouse::getPosition(window));

		window.pollEvent(event);
		if (event.type == Event::Closed || event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			position = MENU;
			
		if (txt2[0].getGlobalBounds().contains(mouse) &&
			event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left)
		{
			music.play();
			file.open("data/file1.txt", ios::out);
			file<<'1';
			file.close();
		}

		else if (txt2[1].getGlobalBounds().contains(mouse) &&
			event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left)
		{
			music.pause();
			file.open("data/file1.txt", ios::out);
			file << '0';
			file.close();
		}

		for (int i = 0; i<count; i++)
			if (txt2[i].getGlobalBounds().contains(mouse))
				txt2[i].setColor(Color::Cyan);
			else txt2[i].setColor(Color::White);

		window.clear();

		for (int i = 0; i<count; i++)
			window.draw(txt1[i]);
		for (int i = 0; i<count; i++)
			window.draw(txt2[i]);

		window.draw(title);
		window.display();
	}
}

void Game::openFile()
{
	try
	{
		file.open("data/statusMusic.txt");
		if (!file.good())
		{
			Error *wsk;
			wsk = new ErrorFile;
			throw wsk;
		}
		
	}
	catch (Error *w)
	{
		w->error();
	}
}

void Game::play()
{

	for (size_t i = 1; i <= numberOfLevels; i++)
	{
		CurrentLevel currLvl(window, position);
		currLvl.runEngine(i);
	}

	position = MENU;
	return;
	
}