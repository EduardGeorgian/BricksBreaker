#pragma once
#include "Menu.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "PauseScreen.h"
#include "LossScreen.h"
#include "WinScreen.h"
#include <random>


class Game {
private:
	sf::RenderWindow gameWindow;
	void processEvents();
	void initWindow();
	void update(sf::Time deltaTime);
	void render();

	sf::Texture paddleTexture;
	sf::RectangleShape paddle;
	sf::Texture ballTexture;
	sf::CircleShape ball;
	sf::Vector2f ballVelocity;
	sf::Text scoreText;
	sf::Font font;
	sf::Texture fallingBonusTexture;
	sf::CircleShape fallingBonus;
	sf::Vector2f fallingBonusVelocity;
	sf::SoundBuffer paddleHitBuffer;
	sf::SoundBuffer brickHitBuffer;
	sf::SoundBuffer bonusHitBuffer;
	sf::Sound paddleHitSound;
	sf::Sound brickHitSound;
	sf::Sound bonusHitSound;
	int score;
	float paddleSpeed;
	bool movingLeft;
	bool movingRight;
	bool isPaused;
	bool isGameOver;
	bool isWin;
	bool bonusActive;
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution;
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	int totalBricks;
	

	sf::Texture brickTexture;
	struct Brick {
		sf::RectangleShape shape;
		bool isDestroyed = false;
	};
	std::vector<Brick> bricks;

public:
	sf::Vector2f prevBallSpeed;
	int prevScore;
	Game();
	void Run();
	void Close();
	sf::RenderWindow& getWindow();
	void initScore(int initialScore);
	void drawScore(sf::RenderWindow& gameWindow);
	void updateScore();
	void initFallingBonus();
	void drawFallingBonus(sf::RenderWindow& gameWindow);
	void resetFallingBonus();
	void setSounds();
	void playPaddleHitSound();
	void playBrickHitSound();
	void playBonusHitSound();
	void resumeGame();
	
};