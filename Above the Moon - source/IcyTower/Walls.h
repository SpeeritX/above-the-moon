#pragma once

#include <SFML\Graphics.hpp>
#include <list>

class Walls
{
public:
	Walls(sf::RenderWindow *window, sf::Vector2f windowSize);
	void draw();
	void move(float x);
	~Walls();

private:
	sf::RenderWindow *window_;
	sf::Vector2f windowSize_;

	sf::Texture textureWallLeft_;
	sf::Texture textureWallRight_;

	std::list<sf::Sprite> wallLeft_;
	std::list<sf::Sprite> wallRight_;
};

