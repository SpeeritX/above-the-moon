// IcyTower.cpp : Defines the entry point for the console application.
//


#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include "Game.h"
#include "Menu.h"

enum GameState {MENU, GAME};

int main()
{
	const int WIN_HEIGHT = 720;
	const int WIN_WIDTH = 600;

	std::srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "IcyTower");

	window.setVerticalSyncEnabled(true);

	int highScore = 0;

	std::fstream fileScore;
	fileScore.open("highscore.dat");
	if (fileScore.is_open() == false)
	{
		//std::cout << "highscore.dat doesn't exist" << std::endl;
		fileScore.open("highscore.dat", std::ios::out | std::ios::in | std::ios::trunc);
		fileScore << highScore;
	}
	else
	{
		fileScore >> highScore;
	}
	fileScore.close();


	Menu menu(&window, sf::Vector2f(WIN_WIDTH, WIN_HEIGHT), highScore);
	Game game(&window, sf::Vector2f(WIN_WIDTH, WIN_HEIGHT), highScore);




	GameState state = MENU;

	sf::Clock clock;
	float elapsedTime = 0;
	float frameTime = 0;
	sf::Clock clockDraw;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (state == MENU && event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Up)
				{
					menu.nextButton();
				}

				if (event.key.code == sf::Keyboard::Down)
				{
					menu.nextButton();
				}

				if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space)
				{
					menu.chooseButton();
				}
			}

		}

		elapsedTime += clock.restart().asSeconds();

		if (elapsedTime > 1.0 / 60)
		{
			elapsedTime -= 1.0 / 60;

			if (state == MENU)
			{
				if (menu.update() == false)
				{
					state = GAME;
					game.reset();
				}
			}
			else if (state == GAME)
			{
				if (game.update() == false)
				{
					state = MENU;
					highScore = game.getHighscore();
					menu.setHighScore(highScore);
				}
			}

		}
		window.clear();


		frameTime += clockDraw.restart().asSeconds();


		if (state == MENU)
		{
			menu.draw();
		}
		else if (state == GAME)
		{
			game.draw();
		}

		window.display();


	}

	return 0;
}