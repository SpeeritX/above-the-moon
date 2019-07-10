#pragma once

#include <SFML\Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string>

enum FocusedButton {START, EXIT};

class Menu
{
public:
	Menu(sf::RenderWindow *win, sf::Vector2f windowSize, int highScore);

	bool update();
	void draw();
	void nextButton();
	void chooseButton();
	void setHighScore(int newHighScore);

	~Menu();


private:
	sf::RenderWindow *window_;
	sf::Vector2f windowSize_;

	sf::Texture textureBackground_;
	sf::Texture textureButtonStart_;
	sf::Texture texturePButtonStart_;
	sf::Texture textureButtonExit_;
	sf::Texture texturePButtonExit_;

	sf::Sprite background_;
	sf::Sprite buttonStart_;
	sf::Sprite pButtonStart_;
	sf::Sprite buttonExit_;
	sf::Sprite pButtonExit_;

	sf::Font font_;
	sf::Text textHighscore_;
	sf::Text textCredits_;

	int highScore_;
	FocusedButton focusedButton_;
	bool isButtonChosen;
};

