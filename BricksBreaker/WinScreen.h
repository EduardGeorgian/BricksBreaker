#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Audio.hpp>


class WinScreen
{
private:
	sf::RenderWindow winWindow;
	sf::Font font;
	sf::Text winText;
	sf::Text scoreText;
	sf::Text playAgainText;
	sf::Text exitText;
	sf::SoundBuffer buffer;
	sf::Sound sound;
	int selectedItemIndex;
public:
	WinScreen(float width, float height);
	bool run(sf::RenderWindow&window,bool isWin);
	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem();
	void setSound();
	void playSound();


};

