#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Menu.h"

class PauseScreen
{
private:
	sf::RenderWindow pauseWindow;
	sf::Font font;
	sf::Text pauseText;
	sf::Text resumeText;
	sf::Text menuText;
	sf::Text exitText;
	int selectedItemIndex;
public:
	PauseScreen(float width, float height);
	void run(sf::RenderWindow& gameWindow);
	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem();

};

