#include "GameOverScreen.h"
#include <iostream>


GameOverScreen::GameOverScreen(sf::RenderWindow *win, sf::Vector2f windowSize, sf::Font *font)
	: window_(win), windowSize_(windowSize), font_(font), opacity(0), bgOpacity(0)
{
	texturebackground_.loadFromFile("images/backgroundGameOver.png");
	background_.setTexture(texturebackground_);
	background_.setColor(sf::Color(255, 255, 255, opacity));

	textGameOver_.setFont(*font_);
	textScore_.setFont(*font_);
	textPoints_.setFont(*font_);

	textGameOver_.setCharacterSize(80);
	textScore_.setCharacterSize(40);
	textPoints_.setCharacterSize(80);

	textGameOver_.setString("GAME OVER");
	textGameOver_.setPosition((windowSize_.x - textGameOver_.getGlobalBounds().width) / 2, 150);
	textGameOver_.setFillColor(sf::Color(255, 255, 255, opacity));
	textScore_.setString("SCORE:");
	textScore_.setPosition((windowSize_.x - textScore_.getGlobalBounds().width) / 2, 320);
	textScore_.setFillColor(sf::Color(174, 214, 26, opacity));

	textPoints_.setFillColor(sf::Color(174, 214, 26, opacity));																	//(160, 190, 50
}

void GameOverScreen::setScore(int score)
{
	textPoints_.setString(std::to_string(score));
	textPoints_.setPosition((windowSize_.x - textPoints_.getGlobalBounds().width) / 2, 350);
}

void GameOverScreen::update()
{
	if (opacity < 255)
	{
		opacity += 13;
		if (opacity > 255)
			opacity = 255;

		textGameOver_.setFillColor(sf::Color(255, 255, 255, opacity));
		textScore_.setFillColor(sf::Color(174, 214, 26, opacity));
		textPoints_.setFillColor(sf::Color(174, 214, 26, opacity));
	}
	
	if (bgOpacity < 255)
	{
		bgOpacity += 3;
		if (bgOpacity > 255)
			bgOpacity = 255;

		background_.setColor(sf::Color(255, 255, 255, bgOpacity));
	}
	
}

void GameOverScreen::draw()
{
	window_->draw(background_);
	window_->draw(textGameOver_);
	window_->draw(textScore_);
	window_->draw(textPoints_);
}

void GameOverScreen::reset()
{
	opacity = 0;
	bgOpacity = 0;
	background_.setColor(sf::Color(255, 255, 255, bgOpacity));
	textGameOver_.setFillColor(sf::Color(174, 214, 26, opacity));
	textScore_.setFillColor(sf::Color(174, 214, 26, opacity));
	textPoints_.setFillColor(sf::Color(174, 214, 26, opacity));
}


GameOverScreen::~GameOverScreen()
{
}
