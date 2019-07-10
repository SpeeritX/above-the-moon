#pragma once

#include <vector>
#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>

enum Direction{FORWARD, BACKWARD};

class Animation
{
public:
	Animation();
	Animation(std::string path, int amountOfFrames);
	void setTexture(std::string path, int amountOfFrames);
	void update(sf::Sprite *playerSprite, float speed);
	void resetAnim(sf::Sprite *playerSprite, float speed);

	~Animation();

private:
	sf::Texture texture_;
	int amountOfFrames_;
	int frameWidth_;
	int frameHeight_;
	Direction direction_;
	int currentFrame_;
	int oneFrameTime_;
	int time_;
};

