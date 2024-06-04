#include "Game.h"
#include "Instructions.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Bricks Breaker", sf::Style::Close | sf::Style::Titlebar);
	Menu menu(window.getSize().x, window.getSize().y);
	menu.run();



    return 0;
}