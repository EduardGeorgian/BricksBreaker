#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
class LossScreen
{
private:
	sf::RenderWindow lossWindow;
	sf::Font font;
	sf::Text lossText;
	sf::Text exitText;
	sf::Text PlayAgain;
	int selectedItemIndex;
public:
	LossScreen(float width, float height);
	void run(sf::RenderWindow& gameWindow, bool isLost);
	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem();
};

