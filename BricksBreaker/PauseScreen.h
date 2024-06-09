#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Menu.h"
#include <SFML/Audio.hpp>

class PauseScreen
{
private:
	sf::RenderWindow pauseWindow;
	sf::Font font;
	sf::Text pauseText;
	sf::Text resumeText;
	sf::Text menuText;
	sf::Text exitText;
	sf::SoundBuffer buffer;
	sf::Sound sound;
	int selectedItemIndex;
public:
	PauseScreen(float width, float height);
	bool run(sf::RenderWindow& gameWindow);
	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem();
	void setSound();
	void playSound();

};

