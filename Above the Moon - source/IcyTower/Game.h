#pragma once

#include "Player.h"
#include "Background.h"
#include "Walls.h"
#include "StatusBar.h"
#include "GameOverScreen.h"
#include "ComboText.h"
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <list>
#include <array>
#include <cstdlib>
#include <fstream>
#include <string>

class Game
{
public:
	Game(sf::RenderWindow *win, sf::Vector2f windowSize, int highScore);
	
	void reset();
	void draw();
	bool update();
	int getHighscore();

	~Game();

private:
	const float SPEED_MODIFIER_AFTER_WALL = -0.7;
	static const int PLATFORM_HEIGHT = 40;
	static const int WALL_WIDTH = 60;
	static const int SPACE_BETWEEN_PLATFORMS = 60;
	static const int AMOUNT_OF_TEXTURES = 13;
	static const int MAX_COMBO_TIME = 80;
	const float MAX_WORLD_SPEED = 11;
	const float SPEED_MODIFIER = 0.0015;

	std::array<sf::Texture, AMOUNT_OF_TEXTURES> platformsTextures_;
	
	sf::RenderWindow *window_;
	sf::Vector2f windowSize_;

	sf::Vector2f canvasSize_;
	
	std::list<std::pair<sf::Sprite, int>> platforms_;
	std::list<ComboText> comboTexts_;
	Player *player_;
	Background *background;
	Walls *walls;
	StatusBar *statusBar_;
	GameOverScreen *gameOverScreen_;
	
	int minMusicVolume_;
	int highScore_;
	int floor;
	int platformNr;
	bool isCombo;
	float comboTime;
	int comboPoints;
	int points;
	float worldSpeed_;
	bool isGameOn_;
	bool isGameOver_;
	std::pair<sf::Sprite, int> playerPlatform_;

	sf::Font font;
	sf::Text textPoints;
	sf::Music music;

	
	void getTextures();
	void movePlayer();
	void moveWorld(float x);
	void resetCombo();
	bool updatePlatforms();
	void updateComboTexts();

};

