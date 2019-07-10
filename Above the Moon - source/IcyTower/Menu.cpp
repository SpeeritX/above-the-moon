#include "Menu.h"



Menu::Menu(sf::RenderWindow *win, sf::Vector2f windowSize, int highScore)
	:window_(win), windowSize_(windowSize), isButtonChosen(false), highScore_(highScore)
{
	textureBackground_.loadFromFile("images/menuBackground2.png");
	textureButtonStart_.loadFromFile("images/buttonStart.png");
	texturePButtonStart_.loadFromFile("images/pushedButtonStart.png");
	textureButtonExit_.loadFromFile("images/buttonExit.png");
	texturePButtonExit_.loadFromFile("images/pushedButtonExit.png");

	background_.setTexture(textureBackground_);
	buttonStart_.setTexture(textureButtonStart_);
	pButtonStart_.setTexture(texturePButtonStart_);
	buttonExit_.setTexture(textureButtonExit_);
	pButtonExit_.setTexture(texturePButtonExit_);

	/*textureButtonStart_.setSmooth(true);
	texturePButtonStart_.setSmooth(true);
	textureButtonExit_.setSmooth(true);
	texturePButtonExit_.setSmooth(true);*/

	buttonStart_.setPosition((windowSize_.x - buttonStart_.getGlobalBounds().width) / 2, 350);
	pButtonStart_.setPosition((windowSize_.x - pButtonStart_.getGlobalBounds().width) / 2,
		350 - (pButtonStart_.getGlobalBounds().width - buttonStart_.getGlobalBounds().width) / 2);

	buttonExit_.setPosition((windowSize_.x - buttonExit_.getGlobalBounds().width) / 2, 450);
	pButtonExit_.setPosition((windowSize_.x - pButtonExit_.getGlobalBounds().width) / 2,
		450 - (pButtonExit_.getGlobalBounds().width - buttonExit_.getGlobalBounds().width) / 2);

	focusedButton_ = START;

	font_.loadFromFile("Organo.ttf");
	textHighscore_.setFont(font_);
	textHighscore_.setFillColor(sf::Color::Color(110, 120, 120));
	textHighscore_.setCharacterSize(38);
	textHighscore_.setString("HIGHSCORE:" + std::to_string(highScore_));
	textHighscore_.setPosition((windowSize_.x - textHighscore_.getGlobalBounds().width) / 2, 620);

	textCredits_.setFont(font_);
	textCredits_.setFillColor(sf::Color::Color(110, 120, 120));
	textCredits_.setCharacterSize(11);
	textCredits_.setString("Music by pheonton on CC-BY 3.0 license.");
	textCredits_.setPosition((windowSize_.x - textCredits_.getGlobalBounds().width) / 2, 705);
}


bool Menu::update()
{
	if (isButtonChosen)
	{
		isButtonChosen = false;
		if (focusedButton_ == START)
		{
			return false;
		}
		else if (focusedButton_ == EXIT)
		{
			window_->close();
		}
	}


	return true;
}

void Menu::draw()
{
	window_->draw(background_);
	window_->draw(textHighscore_);
	window_->draw(textCredits_);

	if (focusedButton_ == START)
	{
		window_->draw(pButtonStart_);
		window_->draw(buttonExit_);
	}
	else
	{
		window_->draw(buttonStart_);
		window_->draw(pButtonExit_);
	}
}

Menu::~Menu()
{
}

void Menu::nextButton()
{
	if (focusedButton_ == START)
	{
		focusedButton_ = EXIT;
	}
	else if (focusedButton_ == EXIT)
	{
		focusedButton_ = START;
	}
}

void Menu::chooseButton()
{
	isButtonChosen = true;
}

void Menu::setHighScore(int newHighScore)
{
	highScore_ = newHighScore;
	textHighscore_.setString("HIGHSCORE:" + std::to_string(highScore_));
	textHighscore_.setPosition((windowSize_.x - textHighscore_.getGlobalBounds().width) / 2, 620);
}
