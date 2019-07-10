#include "Player.h"


Player::Player(sf::RenderWindow *win)
	:speed_({ 0, 0 }), movementAcceleration_(0.21), jumpAcceleration_(-17),
	gravity_(1), friction_(0.92), size_({ 30, 90 }),
	window_(win), state(WALKING), currentAnimation(IDLE)
{
	animations[IDLE].setTexture("images/idleAnim.png", 4);
	animations[LEFT].setTexture("images/leftAnim.png", 4);
	animations[RIGHT].setTexture("images/rightAnim.png", 4);
	animations[JUMP].setTexture("images/jumpAnim.png", 4);

	animations[IDLE].resetAnim(&sprite_, 0);

	jumpSoundBuffer_.loadFromFile("sounds/jump2.wav");
	jumpSound_.setBuffer(jumpSoundBuffer_);
}

void Player::setPosition()
{
	sf::Vector2f pos = position_;
	pos.x -= (sprite_.getLocalBounds().width - size_.x) / 2;
	sprite_.setPosition(pos);
}


void Player::draw()
{
	setPosition();
	window_->draw(sprite_);
}

void Player::update()
{
	readKeys();

	if (state == WALKING)
	{
		//std::cout << "Player's speed_.x: " << speed_.x << std::endl;
		if (speed_.x > 0.6)
		{
			if (currentAnimation == RIGHT)
				animations[RIGHT].update(&sprite_, abs(speed_.x));
			else
				animations[RIGHT].resetAnim(&sprite_, abs(speed_.x)), currentAnimation = RIGHT;
		}
		else if(speed_.x < -0.6)
		{
			if (currentAnimation == LEFT)
				animations[LEFT].update(&sprite_, abs(speed_.x));
			else
				animations[LEFT].resetAnim(&sprite_, abs(speed_.x)), currentAnimation = LEFT;
		}
		else
		{
			if (currentAnimation == IDLE)
				animations[IDLE].update(&sprite_, 0);
			else
				animations[IDLE].resetAnim(&sprite_, 0), currentAnimation = IDLE;
		}
	}
	else
	{
		if (currentAnimation == JUMP)
			animations[JUMP].update(&sprite_, 0.3 * abs(speed_.y));
		else
			animations[JUMP].resetAnim(&sprite_, 0.3 * abs(speed_.y)), currentAnimation = JUMP;
	}
}

void Player::move(float x)
{
	position_.y += x;
}



void Player::readKeys()
{

	//if (state == WALKING)
	//{
	//	state = JUMPING;
	//	speed_.y = jumpAcceleration_ + -1.4 * abs(speed_.x);
	//}

	//if (speed_.x <= 0)
	//{
	//	if (speed_.x > 0)
	//		speed_.x *= friction_ * friction_;

	//	speed_.x -= movementAcceleration_;//  -0.03 * speed_.x;
	//}
	//else if (speed_.x > 0)
	//{
	//	if (speed_.x < 0)
	//		speed_.x *= friction_ * friction_;

	//	speed_.x += movementAcceleration_;// +0.03 * speed_.x;
	//}
	//else
	//{
	//	speed_.x *= friction_;
	//}

	//std::cout << "PLAYER SPEED: " << speed_.x << std::endl;


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && state == WALKING)
	{
		jumpSound_.play();
		state = JUMPING;
		speed_.y = jumpAcceleration_ +  -1.4 * abs(speed_.x);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if(speed_.x > 0)
			speed_.x *= friction_ * friction_;

		speed_.x -= movementAcceleration_;//  -0.03 * speed_.x;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (speed_.x < 0)
			speed_.x *= friction_ * friction_;

		speed_.x += movementAcceleration_;// +0.03 * speed_.x;
	}
	else
	{
		speed_.x *= friction_;
	}

	
	if (speed_.x > -0.1 && speed_.x < 0.1)
	{
		speed_.x = 0;
	}
}



Player::~Player()
{
}
