#pragma once

#include <SFML\Graphics.hpp>
#include <cmath>

class ComboText
{
public:
	ComboText(sf::RenderWindow *win, sf::Vector2f windowSize, sf::Vector2f position, sf::Font *font, int points);

	bool update();
	void draw();
	void move(sf::Vector2f direction);
	~ComboText();

private:
	static const int MIN_LIFE_TIME = 49;
	static const int MAX_LIFE_TIME = 50;
	static const int MIN_FONT_SIZE = 49;
	static const int MAX_FONT_SIZE = 50;
	static const int SPEED = 6;

	sf::RenderWindow *window_;
	sf::Vector2f windowSize_;

	sf::Font *font_;

	sf::Text textPoints_;
	sf::Vector2f direction_;

	int lifeTime;
	int opacity_;
	
};

