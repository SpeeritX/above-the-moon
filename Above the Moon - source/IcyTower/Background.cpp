#include "Background.h"



Background::Background(sf::RenderWindow *window, sf::Vector2f windowSize)
	:window_(window), windowSize_(windowSize), speed_(.00005)
{
	textureSky_.loadFromFile("images/sky.png");
	spriteSky_.setTexture(textureSky_);

	textureMoon_.loadFromFile("images/backgroundMoon3.png");
	spriteMoon_.setTexture(textureMoon_);

	textureSky_.setSmooth(true);
	textureMoon_.setSmooth(true);

	spriteSky_.setPosition(0, windowSize_.y - spriteSky_.getLocalBounds().height);
	spriteMoon_.setPosition(0, -930); // -930
}

void Background::reset()
{
	speed_ = 0.00005;
	spriteSky_.setPosition(0, windowSize_.y - spriteSky_.getLocalBounds().height);
	spriteMoon_.setPosition(0, -930);
}

void Background::draw()
{
	window_->draw(spriteSky_);
	window_->draw(spriteMoon_);
}

void Background::move(float x)
{
	spriteSky_.move(0, spriteSky_.getPosition().y * -speed_ * x);
	spriteMoon_.move(0, (windowSize_.y - 790 - spriteMoon_.getPosition().y) * x * speed_);
}


Background::~Background()
{
}
