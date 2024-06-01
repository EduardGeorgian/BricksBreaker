#include "LossScreen.h"


LossScreen::LossScreen(float width, float height)
{
	if (!font.loadFromFile("D:/C++Games/BricksBreaker/BricksBreaker/Fonturi/arial.ttf"))
	{
		std::cout << "Error loading font" << std::endl;
	}
	lossText.setFont(font);
	lossText.setString("YOU LOST!");
	lossText.setCharacterSize(50);
	lossText.setFillColor(sf::Color::White);
	lossText.setPosition(sf::Vector2f(width / 2 -150, height / 2 - 300));

	PlayAgain.setFont(font);
	PlayAgain.setString("Play Again");
	PlayAgain.setCharacterSize(30);
	PlayAgain.setFillColor(sf::Color::White);
	PlayAgain.setPosition(sf::Vector2f(width / 2 - 100, height / 2 - 100));

	exitText.setFont(font);
	exitText.setString("EXIT");
	exitText.setCharacterSize(30);
	exitText.setFillColor(sf::Color::White);
	exitText.setPosition(sf::Vector2f(width / 2 - 100, height / 2 ));

	selectedItemIndex = 1;
}


void::LossScreen::draw(sf::RenderWindow& window)
{
	window.draw(lossText);
	window.draw(PlayAgain);
	window.draw(exitText);
}




void::LossScreen::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		switch (selectedItemIndex)
		{
		case 1:
			PlayAgain.setFillColor(sf::Color::White);
			break;
		case 2:
			exitText.setFillColor(sf::Color::White);
			break;
		}
		selectedItemIndex--;
		switch (selectedItemIndex)
		{
		case 1:
			PlayAgain.setFillColor(sf::Color::Red);
			break;
		case 2:
			exitText.setFillColor(sf::Color::Red);
			break;
		}
	}
}


void::LossScreen::MoveDown()
{
	if (selectedItemIndex + 1 < 3)
	{
		switch (selectedItemIndex)
		{
		case 1:
			PlayAgain.setFillColor(sf::Color::White);
			break;
		case 2:
			exitText.setFillColor(sf::Color::White);
			break;
		}
		selectedItemIndex++;
		switch (selectedItemIndex)
		{
		case 1:
			PlayAgain.setFillColor(sf::Color::Red);
			break;
		case 2:
			exitText.setFillColor(sf::Color::Red);
			break;
		}
	}
}


int::LossScreen::GetPressedItem()
{
	return selectedItemIndex;
}



void::LossScreen::run(sf::RenderWindow& gameWindow, bool isLost)
{
	lossWindow.create(sf::VideoMode(800, 600), "Game Over!", sf::Style::Close | sf::Style::Titlebar);
	
	while (lossWindow.isOpen() && isLost)
	{
		sf::Event event;
		while (lossWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				lossWindow.close();
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Up)
				{
					MoveUp();
				}
				if (event.key.code == sf::Keyboard::Down)
				{
					MoveDown();
				}
				if (event.key.code == sf::Keyboard::Return)
				{
					switch (GetPressedItem())
					{
					case 1:
						isLost = false;
						lossWindow.close();
						{
							Game game;
							game.Run();
						}
						break;
					case 2:
						lossWindow.close();
						gameWindow.close();
						break;
					}
				}
			}
		}
		lossWindow.clear();
		draw(lossWindow);
		lossWindow.display();
	}
}