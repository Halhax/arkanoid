#pragma once
#include "Error.h"
#include "Game.h"
#include <Windows.h>

class ErrorFont : protected Game, public Error
{
public:

	virtual void error()
	{
		RenderWindow window(VideoMode(800, 600), "ERROR !");

		window.clear(Color::Blue);

		window.display();
		Sleep(5000);
		exit(0);
	}


};