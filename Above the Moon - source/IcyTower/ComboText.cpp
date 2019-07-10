#include "ComboText.h"



ComboText::ComboText(sf::RenderWindow *win, sf::Vector2f windowSize, sf::Vector2f position, sf::Font *font, int points)
	:window_(win), windowSize_(windowSize), font_(font), opacity_(255)
{
	textPoints_.setFillColor(sf::Color(160, 190, 50, opacity_));
	textPoints_.setOutlineColor(sf::Color(0, 0, 0, opacity_));
	textPoints_.setOutlineThickness(3);
	textPoints_.setFont(*font_);
	textPoints_.setString(std::to_string(points));
	textPoints_.setPosition(position);
	textPoints_.setCharacterSize(rand() % (MAX_FONT_SIZE - MIN_FONT_SIZE) + MIN_FONT_SIZE);

	lifeTime = rand() % (MAX_LIFE_TIME - MIN_LIFE_TIME) + MIN_LIFE_TIME;
	
	direction_.x = 0;
	direction_.y = -SPEED;
}

bool ComboText::update()
{
	lifeTime--;

	if (lifeTime < 10)
	{
		opacity_ = 255 * (lifeTime / 10.0f);
		textPoints_.setFillColor(sf::Color(160, 190, 50, opacity_));
		textPoints_.setOutlineColor(sf::Color(0, 0, 0, opacity_));
	}

	move(direction_);

	if (lifeTime < 0)
		return false;

	return true; 
}

void ComboText::draw()
{
	window_->draw(textPoints_);
}


ComboText::~ComboText()
{
}

void ComboText::move(sf::Vector2f direction)
{
	textPoints_.move(direction);
}
