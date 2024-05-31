#pragma once
#include "Menu.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "PauseScreen.h"

class Game {
private:
	sf::RenderWindow gameWindow;
	void processEvents();
	void initWindow();
	void update(sf::Time deltaTime);
	void render();
public:
	sf::RenderWindow& getWindow();
	Game();
	void Run();
	void Close();
};