#pragma once
#include "Menu.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "PauseScreen.h"
#include "LossScreen.h"

class Game {
private:
	sf::RenderWindow gameWindow;
	void processEvents();
	void initWindow();
	void update(sf::Time deltaTime);
	void render();


	sf::RectangleShape paddle;
	sf::CircleShape ball;
	sf::Vector2f ballVelocity;
	float paddleSpeed;
	bool movingLeft;
	bool movingRight;
	bool isPaused;
	bool isGameOver;
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

	struct Brick {
		sf::RectangleShape shape;
		bool isDestroyed = false;
	};
	std::vector<Brick> bricks;

public:
	
	Game();
	void Run();
	void Close();
	sf::RenderWindow& getWindow();
};