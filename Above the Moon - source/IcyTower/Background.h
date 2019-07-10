#pragma once

#include <SFML\Graphics.hpp>

class Background
{
public:
	Background(sf::RenderWindow *window, sf::Vector2f windowSize);
	void reset();
	void draw();
	void move(float x);
	~Background();

private:
	float speed_;
	sf::Vector2f windowSize_;
	sf::RenderWindow *window_;
	sf::Texture textureSky_;
	sf::Sprite spriteSky_;
	sf::Texture textureMoon_;
	sf::Sprite spriteMoon_;
};

