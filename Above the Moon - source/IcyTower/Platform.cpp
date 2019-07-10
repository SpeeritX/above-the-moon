#include "Platform.h"



Platform::Platform(sf::RenderWindow *win, sf::Vector2f position)
	:window_(win)
{
}


Platform::Platform(sf::RenderWindow *win, sf::Vector2f position, int width)
	: window_(win)
{
	switch (width)
	{
	case 12:
		if (!texture_.loadFromFile("images/platform12.png"))
		{
			std::cout << "Loading platform12's texture failed" << std::endl;
		}
		sprite_.setTexture(texture_);
		break;

	default:
		std::cout << "Constructor: Invalid width of the platform." << std::endl;
		break;
	}

	position_ = position;
}

void Platform::draw()
{

	
	sprite_.setPosition(position_);
	window_->draw(sprite_);
}

Platform::~Platform()
{
}
