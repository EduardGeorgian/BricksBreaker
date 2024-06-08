#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include "Instructions.h"
#include <SFML/Audio.hpp>




#define MAX_NUMBER_OF_ITEMS 3

class Menu {
private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
	sf::SoundBuffer buffer;
	sf::Sound sound;
public:
	Menu(float width, float height);
	void run();
	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem();
	void setSound();
	void playSound();
	void stopSound();

};