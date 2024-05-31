#include "Instructions.h"


Instructions::Instructions(float width, float height)
{
	instructionsWindow.create(sf::VideoMode(width, height), "Instructions", sf::Style::Close | sf::Style::Titlebar);
	font.loadFromFile("D:/C++Games/BricksBreaker/BricksBreaker/Fonturi/arial.ttf");
	instructions.setFont(font);
	instructions.setString("Instructions:\n\n"
		"1. Use the paddle to bounce the ball and break the bricks.\n"
		"2. The ball will bounce off the paddle and the walls.\n"
		"3. The ball will break the bricks when it hits them.\n"
		"4. The game is over when the ball falls off the screen.\n"
		"5. Press 'P' to pause the game.\n"
		"6. Press 'R' to resume the game.\n"
		"7. Press 'Esc' to exit the game.\n\n"
		"Press 'Esc' to return to the main menu.");
	instructions.setCharacterSize(15);
	instructions.setFillColor(sf::Color::White);
	instructions.setPosition(width / 2 - instructions.getGlobalBounds().width / 2, height / 2 - instructions.getGlobalBounds().height / 2);
}

void Instructions::run()
{
	Menu menu(instructionsWindow.getSize().x, instructionsWindow.getSize().y);
	while (instructionsWindow.isOpen())
	{
		sf::Event event;
		while (instructionsWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				instructionsWindow.close();
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					instructionsWindow.close();
					instructionsWindow.clear();
					menu.run();
				}
			}
		}
		draw(instructionsWindow);
	}
}
void Instructions::draw(sf::RenderWindow& window)
{
	window.clear();
	window.draw(instructions);
	window.display();
}

