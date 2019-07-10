#pragma once

#include <SFML\Graphics.hpp>

class StatusBar
{
public:
	void draw();
	void updateCombo(float comboTime);

	StatusBar(sf::RenderWindow *window, sf::Vector2f windowSize, float maxComboTime);
	~StatusBar();

private:
	sf::RenderWindow *window_;
	sf::Vector2f windowSize_;

	sf::Sprite shadowBar_;
	sf::Sprite lightBar_;
	sf::Sprite darkBar_;
	sf::Sprite barStroke_;

	sf::Texture textureShadowBar_;
	sf::Texture textureLightBar_;
	sf::Texture textureDarkBar_;
	sf::Texture textureBarStroke_;

	float maxComboTime_;
};

