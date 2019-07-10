#pragma once

#include <SFML\Graphics.hpp>

class GameOverScreen
{
public:
	GameOverScreen(sf::RenderWindow *win, sf::Vector2f windowSize, sf::Font *font);

	void setScore(int score);
	void update();
	void draw();
	void reset();

	~GameOverScreen();

private:
	sf::RenderWindow *window_;
	sf::Vector2f windowSize_;

	sf::Texture texturebackground_;
	sf::Sprite background_;
	sf::Font *font_;

	sf::Text textGameOver_;
	sf::Text textScore_;
	sf::Text textPoints_;

	float opacity;
	float bgOpacity;
};

