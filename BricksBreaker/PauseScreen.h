#pragma once
#include <SFML/Graphics.hpp>

#include "Menu.h"
#include <SFML/Audio.hpp>
#include <functional>

class Game;

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
	Game* game;

public:
	
	PauseScreen(float width, float height, Game* gamePointer);
	bool run(sf::RenderWindow& gameWindow);
	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem();
	void setSound();
	void playSound();

	
};

