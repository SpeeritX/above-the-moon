#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Animation.h"
#include <iostream>
#include <cmath>
#include <array>

enum State {WALKING, JUMPING, FALLING};

enum AnimationState{IDLE, LEFT, RIGHT, JUMP};

class Player
{
private:
	float movementAcceleration_;
	float jumpAcceleration_;
	float friction_;

	AnimationState currentAnimation;

	std::array<Animation, 4> animations;


	sf::Sprite sprite_;
	sf::SoundBuffer jumpSoundBuffer_;
	sf::Sound jumpSound_;
	sf::RenderWindow *window_;

	void readKeys();
	void setPosition();

public:
	sf::Vector2f size_;
	sf::Vector2f position_;
	State state;
	sf::Vector2f speed_;
	float gravity_;

	Player(sf::RenderWindow *win);
	
	
	void draw();
	void update();
	void move(float x);

	~Player();
};

