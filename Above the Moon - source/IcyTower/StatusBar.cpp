#include "StatusBar.h"



StatusBar::StatusBar(sf::RenderWindow *window, sf::Vector2f windowSize, float maxComboTime)
	:window_(window), windowSize_(windowSize), maxComboTime_(maxComboTime)
{
	textureShadowBar_.loadFromFile("images/shadowBar.png");
	textureLightBar_.loadFromFile("images/lightBar.png");
	textureDarkBar_.loadFromFile("images/darkBar.png");
	textureBarStroke_.loadFromFile("images/barStroke.png");

	shadowBar_.setTexture(textureShadowBar_);
	lightBar_.setTexture(textureLightBar_);
	darkBar_.setTexture(textureDarkBar_);
	barStroke_.setTexture(textureBarStroke_);

	lightBar_.setPosition(5, 0);

	darkBar_.setPosition(586, 0);
	//3 - 586
}

void StatusBar::draw()
{
	window_->draw(shadowBar_);
	window_->draw(lightBar_);
	window_->draw(darkBar_);
	window_->draw(barStroke_);
}

void StatusBar::updateCombo(float comboTime)
{
	darkBar_.setPosition(comboTime * 586 / maxComboTime_ + 3, 0);
}

StatusBar::~StatusBar()
{
}
