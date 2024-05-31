#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Menu.h"

class Instructions
{
private:
	sf::RenderWindow instructionsWindow;
	sf::Font font;
	sf::Text instructions;
public:
	Instructions(float width, float height);
	void run();
	void draw(sf::RenderWindow& window);
};

