#include "Walls.h"



Walls::Walls(sf::RenderWindow *window, sf::Vector2f windowSize)
	:window_(window), windowSize_(windowSize)
{
	textureWallLeft_.loadFromFile("images/wallLeft.png");
	textureWallRight_.loadFromFile("images/wallRight.png");

	textureWallLeft_.setSmooth(true);
	textureWallRight_.setSmooth(true);

	wallLeft_.push_back(sf::Sprite());
	wallLeft_.back().setTexture(textureWallLeft_);

	wallRight_.push_back(sf::Sprite());
	wallRight_.back().setTexture(textureWallRight_);
	wallRight_.back().setPosition(windowSize_.x - wallRight_.back().getLocalBounds().width, 0);
}

void Walls::draw()
{
	for (auto &it : wallLeft_)
	{
		window_->draw(it);
	}

	for (auto &it : wallRight_)
	{
		window_->draw(it);
	}
}

void Walls::move(float x)
{
	x *= 1.1;
	for (auto &it : wallLeft_)
	{
		it.move(0, x);
	}

	if (wallLeft_.back().getPosition().y >= 0)
	{
		sf::Vector2f pos = wallLeft_.back().getPosition();
		pos.y -= wallLeft_.back().getLocalBounds().height;
		wallLeft_.push_back(sf::Sprite());
		wallLeft_.back().setTexture(textureWallLeft_);
		wallLeft_.back().setPosition(pos);
	}

	if (wallLeft_.front().getPosition().y > windowSize_.y)
	{
		wallLeft_.pop_front();
	}


	for (auto &it : wallRight_)
	{
		it.move(0, x);
	}

	if (wallRight_.back().getPosition().y >= 0)
	{
		sf::Vector2f pos = wallRight_.back().getPosition();
		pos.y -= wallRight_.back().getLocalBounds().height;
		wallRight_.push_back(sf::Sprite());
		wallRight_.back().setTexture(textureWallRight_);
		wallRight_.back().setPosition(pos);
	}

	if (wallRight_.front().getPosition().y > windowSize_.y)
	{
		wallRight_.pop_front();
	}
}


Walls::~Walls()
{
}
