#include "Animation.h"



Animation::Animation()
	: oneFrameTime_(9)
{
}

Animation::Animation(std::string path, int amountOfFrames)
	:amountOfFrames_(amountOfFrames), oneFrameTime_(9)
{
	texture_.loadFromFile(path);

	frameWidth_ = texture_.getSize().x / amountOfFrames_;
	frameHeight_ = texture_.getSize().y;

	time_ = 5;
	currentFrame_ = 0;
	direction_ = FORWARD;
}

void Animation::setTexture(std::string path, int amountOfFrames)
{
	amountOfFrames_ = amountOfFrames;
	texture_.loadFromFile(path);

	frameWidth_ = texture_.getSize().x / amountOfFrames_;
	frameHeight_ = texture_.getSize().y;

	time_ = oneFrameTime_;
	currentFrame_ = 0;
}

void Animation::update(sf::Sprite *playerSprite, float speed)
{
	time_++;
	//std::cout << "OneFrameTime: " << oneFrameTime_ - 0.5*speed << std::endl;
	if (time_ >= oneFrameTime_)
	{
		//oneFrameTime_ = 9 - 0.4*speed;
		
		time_ = 0;
		currentFrame_++;
		if (currentFrame_ == amountOfFrames_)
			currentFrame_ = 0;

		playerSprite->setTextureRect(sf::IntRect(currentFrame_*frameWidth_, 0, frameWidth_, frameHeight_));
	}
}

void Animation::resetAnim(sf::Sprite *playerSprite, float speed)
{
	playerSprite->setTexture(texture_);
	playerSprite->setTextureRect(sf::IntRect(0, 0, frameWidth_, frameHeight_));
	oneFrameTime_ = 9 - 0.4*speed;
	currentFrame_ = 0;
	time_ = 0;
}


Animation::~Animation()
{
}

