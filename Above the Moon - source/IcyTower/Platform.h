#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
class Platform
{
private:
	sf::Texture texture_;
	sf::Sprite sprite_;
	sf::RenderWindow *window_;

	sf::Vector2f position_;

public:
	Platform(sf::RenderWindow *win, sf::Vector2f position);
	Platform(sf::RenderWindow *win, sf::Vector2f position, int width);

	void draw();

	~Platform();
};

