#include "Game.h"



Game::Game(sf::RenderWindow *win, sf::Vector2f windowSize, int highScore)
	:window_(win), windowSize_(windowSize), isGameOn_(false),
	isGameOver_(false), worldSpeed_(2.4), platformNr(0), floor(0), points(0), 
	comboTime(0), isCombo(false), highScore_(highScore), minMusicVolume_(50)
{
	music.openFromFile("sounds/gameMusic.wav");
	music.setLoop(true);
	music.setVolume(minMusicVolume_);
	music.play();

	if (!font.loadFromFile("Organo.ttf"))
	{
		std::cout << "Error during font loading" << std::endl;
	}

	background = new Background(window_, windowSize_);
	walls = new Walls(window_, windowSize_);
	statusBar_ = new StatusBar(window_, windowSize_, MAX_COMBO_TIME);
	gameOverScreen_ = new GameOverScreen(window_, windowSize_, &font);

	canvasSize_.x = windowSize_.x - 2 * WALL_WIDTH;
	canvasSize_.y = windowSize_.y;

	//std::cout << canvasSize_.x << ' ' << canvasSize_.y << std::endl;

	getTextures();
	

	textPoints.setFont(font);

	

	textPoints.setScale(0.8, 0.8);
	textPoints.setFillColor(sf::Color(174, 214, 26));
	
}




void Game::getTextures()
{
	platformsTextures_[12].loadFromFile("images/platform12.png");
	platformsTextures_[8].loadFromFile("images/platform8.png");
	platformsTextures_[7].loadFromFile("images/platform7.png");
	platformsTextures_[6].loadFromFile("images/platform6.png");
	platformsTextures_[5].loadFromFile("images/platform5.png");
	platformsTextures_[4].loadFromFile("images/platform4.png");
	platformsTextures_[3].loadFromFile("images/platform3.png");
	platformsTextures_[2].loadFromFile("images/platform2.png");

	for (auto &it : platformsTextures_)
	{
		it.setSmooth(true);
	}
}

void Game::movePlayer()
{
	if (player_->speed_.x > 0 && 
		player_->position_.x + player_->size_.x + player_->speed_.x >= canvasSize_.x + WALL_WIDTH)
	{
		float distanceToWall = canvasSize_.x + WALL_WIDTH - player_->position_.x - player_->size_.x;
		float percentOfRemainingMove = 1 - distanceToWall / player_->speed_.x;

		player_->speed_.x *= SPEED_MODIFIER_AFTER_WALL;

		player_->position_.x = canvasSize_.x + WALL_WIDTH - player_->size_.x + player_->speed_.x * percentOfRemainingMove;
	}
	else if (player_->speed_.x < 0 && player_->position_.x + player_->speed_.x < WALL_WIDTH)
	{
		float distanceToWall = player_->position_.x - WALL_WIDTH;
		float percentOfRemainingMove = 1 - distanceToWall / player_->speed_.x;

		player_->speed_.x *= SPEED_MODIFIER_AFTER_WALL;

		player_->position_.x = WALL_WIDTH + player_->speed_.x * percentOfRemainingMove;
	}
	else
	{
		player_->position_.x += player_->speed_.x;
	}

	if (player_->state == FALLING || player_->state == JUMPING)
	{
		player_->speed_.y += player_->gravity_;
		if (player_->speed_.y > 0)
			player_->state = FALLING;
	}


	if (player_->state == FALLING)
	{
		bool done = false;
		for (auto &i : platforms_)
		{
			auto &it = i.first;
			if (player_->position_.y  + player_->size_.y < it.getPosition().y &&
				player_->position_.y + player_->size_.y + player_->speed_.y >= it.getPosition().y &&
				player_->position_.x + player_->size_.x > it.getPosition().x &&
				player_->position_.x < it.getPosition().x + it.getLocalBounds().width)
			{
				player_->position_.y = it.getPosition().y - player_->size_.y;
				player_->state = WALKING;
				player_->speed_.y = 0;
				
				//std::cout << "PLATFORMS: " << playerPlatform_.second << "  " << i.second << std::endl;
				if (playerPlatform_.second + 1 < i.second)
				{
					if (comboTime > 0)
					{
						isCombo = true;
					}
					comboTime = MAX_COMBO_TIME;
					comboPoints += i.second - playerPlatform_.second;
				}
				else if (playerPlatform_.second != i.second)
				{
					resetCombo();
				}

				playerPlatform_ = i;

				if(i.second > floor)
					floor = i.second;
				done = true;
				break;
			}
		}
		if (!done)
		{
			player_->position_.y += player_->speed_.y;
		}
	}
	else if (player_->state == WALKING)
	{
		if (player_->position_.x + player_->size_.x < playerPlatform_.first.getPosition().x ||
			player_->position_.x > playerPlatform_.first.getPosition().x + playerPlatform_.first.getLocalBounds().width)
		{
			player_->state = FALLING;
			player_->speed_.y = player_->gravity_;
			player_->position_.y += player_->speed_.y;
		}
	}
	else if (player_->state == JUMPING)
	{
		player_->position_.y += player_->speed_.y;
	}

	if (player_->position_.y < 0.2 * canvasSize_.y)
	{
		moveWorld(0.2 * canvasSize_.y - player_->position_.y);
	}
	else if (player_->position_.y > canvasSize_.y)
	{
		isGameOver_ = true;
		isGameOn_ = false;
		resetCombo();
		int score = floor * 10 + points;
		gameOverScreen_->setScore(score);

		if (score > highScore_)
		{
			highScore_ = score;
			std::fstream fileScore;
			fileScore.open("highscore.dat", std::ios::out | std::ios::in | std::ios::trunc);
			fileScore << score;
			fileScore.close();
		}
	}
}

void Game::moveWorld(float x)
{
	isGameOn_ = true;
	for (auto i = platforms_.begin(); i != platforms_.end(); ++i)
	{
		auto &it = i->first;
		it.move(sf::Vector2f(0, x));
	}
	player_->move(x);
	walls->move(x);
	background->move(x);

	if (worldSpeed_ < MAX_WORLD_SPEED)
	{
		worldSpeed_ += SPEED_MODIFIER;
		if (worldSpeed_ > MAX_WORLD_SPEED)
		{
			worldSpeed_ = MAX_WORLD_SPEED;
		}
		//std::cout << "WORLD SPEED: " << worldSpeed_ << std::endl;
	}

	for (auto &i : comboTexts_)
	{
		i.move(sf::Vector2f(0, x));
	}
}

void Game::resetCombo()
{
	if (isCombo)
	{
		points += comboPoints * 2;
		comboTexts_.push_back(ComboText(window_, windowSize_,player_->position_ ,&font, comboPoints * 2));
	}
	comboTime = 0;
	comboPoints = 0;
	isCombo = false;
}

bool Game::updatePlatforms()
{
	if (platforms_.front().first.getPosition().y > canvasSize_.y)
	{
		platforms_.pop_front();
		//std::cout << "NR: " << platforms_.front().second << std::endl;
	}

	if (platforms_.back().first.getPosition().y > 0)
	{
		sf::Vector2f pos;
		pos.y = platforms_.back().first.getPosition().y - WALL_WIDTH - SPACE_BETWEEN_PLATFORMS;
		
		if (platforms_.back().second % 50 == 49)
		{
			platforms_.push_back({ sf::Sprite(), platformNr++ });
			pos.x = WALL_WIDTH;
			platforms_.back().first.setTexture(platformsTextures_[12]);
			platforms_.back().first.setPosition(pos);

		}
		else
		{ 
			int size;
			if(platformNr < 50)
				size = rand() % 3 + 6;
			else if (platformNr < 100)
				size = rand() % 4 + 5;
			else if (platformNr < 150)
				size = rand() % 5 + 4;
			else if (platformNr < 200)
				size = rand() % 6 + 3;
			else
				 size = rand() % 7 + 2;

			pos.x = WALL_WIDTH + rand() % (int)(canvasSize_.x - size * PLATFORM_HEIGHT);
		
			platforms_.push_back({ sf::Sprite(), platformNr++ });
			platforms_.back().first.setTexture(platformsTextures_[size]);
			platforms_.back().first.setPosition(pos);
		}

		return true;
	}
	return false;
}

void Game::updateComboTexts()
{
	for (auto i = comboTexts_.begin(); i != comboTexts_.end();)
	{
		if (i->update() == false)
		{
			i = comboTexts_.erase(i);
		}
		else
		{
			++i;
		}	
	}
}

void Game::reset()
{

	isGameOn_ = false;
	isGameOver_ = false;
	worldSpeed_ = 2.4;
	platformNr = 0;
	floor = 0;
	points = 0;
	comboTime = 0;
	isCombo = false;

	comboTexts_.clear();

	platforms_.clear();
	platforms_.push_back({ sf::Sprite(), platformNr++ });
	platforms_.back().first.setTexture(platformsTextures_[12]);
	platforms_.back().first.setPosition(WALL_WIDTH, canvasSize_.y - PLATFORM_HEIGHT);
	playerPlatform_ = platforms_.back();

	while (updatePlatforms());

	background->reset();
	gameOverScreen_->reset();

	player_ = new Player(window_);
	player_->position_ = sf::Vector2f(WALL_WIDTH + canvasSize_.x / 2 - player_->size_.x / 2, canvasSize_.y - PLATFORM_HEIGHT - player_->size_.y);
}

void Game::draw()
{
	background->draw();
	for (auto &i : platforms_)
	{
		auto &it = i.first;
		window_->draw(it);
	}

	player_->draw();
	walls->draw();
	statusBar_->draw();
	textPoints.setPosition(sf::Vector2f((windowSize_.x - textPoints.getGlobalBounds().width) / 2, 23));
	window_->draw(textPoints);

	for (auto &i : comboTexts_)
	{
		i.draw();
	}

	if (isGameOver_ == true)
	{
		gameOverScreen_->draw();
	}
}

bool Game::update()
{
	

	updateComboTexts();
	if (isGameOver_ == false)
	{
		if (music.getVolume() < 100)
		{
			music.setVolume(music.getVolume() + 1);
		}

		if (comboTime > 0)
		{
			comboTime -= 0.75;
			if (comboTime <= 0)
			{
				resetCombo();
			}
		}

		statusBar_->updateCombo(comboTime);

		updatePlatforms();
		player_->update();
		movePlayer();

		if (isGameOn_)
		{
			moveWorld(worldSpeed_);
		}
		textPoints.setString(std::to_string(floor * 10 + points));

	}
	else if (isGameOver_ == true)
	{
		if (music.getVolume() > minMusicVolume_)
		{
			music.setVolume(music.getVolume() - 1);
		}

		if (worldSpeed_ > 0.1)
		{
			worldSpeed_ *= 0.95;
			moveWorld(worldSpeed_);
			gameOverScreen_->update();
		}
		else
		{
			gameOverScreen_->update();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
				return false;
			}
			
		}
	}


	return true;
}

int Game::getHighscore()
{
	return highScore_;
}

Game::~Game()
{
}
