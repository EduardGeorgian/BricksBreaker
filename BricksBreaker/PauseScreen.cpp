#include "PauseScreen.h"


PauseScreen::PauseScreen(float width, float height)
{
	if (!font.loadFromFile("D:/C++Games/BricksBreaker/BricksBreaker/Fonturi/arial.ttf"))
	{
		std::cout << "Error loading font" << std::endl;
	}
	pauseText.setFont(font);
	pauseText.setString("PAUSED");
	pauseText.setCharacterSize(50);
	pauseText.setFillColor(sf::Color::White);
	pauseText.setPosition(sf::Vector2f(width / 2 - 100, height / 2 - 200));

	resumeText.setFont(font);
	resumeText.setString("RESUME");
	resumeText.setCharacterSize(30);
	resumeText.setFillColor(sf::Color::White);
	resumeText.setPosition(sf::Vector2f(width / 2 - 100, height / 2 - 100));

	menuText.setFont(font);
	menuText.setString("MENU");
	menuText.setCharacterSize(30);
	menuText.setFillColor(sf::Color::White);
	menuText.setPosition(sf::Vector2f(width / 2 - 100, height / 2));

	exitText.setFont(font);
	exitText.setString("EXIT");
	exitText.setCharacterSize(30);
	exitText.setFillColor(sf::Color::White);
	exitText.setPosition(sf::Vector2f(width / 2 - 100, height / 2 + 100));

	selectedItemIndex = 1;
}

void PauseScreen::draw(sf::RenderWindow& window)
{
	window.draw(pauseText);
	window.draw(resumeText);
	window.draw(menuText);
	window.draw(exitText);
}

void PauseScreen::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		switch (selectedItemIndex)
		{
		case 1:
			resumeText.setFillColor(sf::Color::White);
			break;
		case 2:
			menuText.setFillColor(sf::Color::White);
			break;
		case 3:
			exitText.setFillColor(sf::Color::White);
			break;
		}
		selectedItemIndex--;
		switch (selectedItemIndex)
		{
		case 1:
			resumeText.setFillColor(sf::Color::Red);
			break;
		case 2:
			menuText.setFillColor(sf::Color::Red);
			break;
		case 3:
			exitText.setFillColor(sf::Color::Red);
			break;
		}
	}
}

void PauseScreen::MoveDown()
{
	if (selectedItemIndex + 1 < 4)
	{
		switch (selectedItemIndex)
		{
		case 1:
			resumeText.setFillColor(sf::Color::White);
			break;
		case 2:
			menuText.setFillColor(sf::Color::White);
			break;
		case 3:
			exitText.setFillColor(sf::Color::White);
			break;
		}
		selectedItemIndex++;
		switch (selectedItemIndex)
		{
		case 1:
			resumeText.setFillColor(sf::Color::Red);
			break;
		case 2:
			menuText.setFillColor(sf::Color::Red);
			break;
		case 3:
			exitText.setFillColor(sf::Color::Red);
			break;
		}
	}
}

int PauseScreen::GetPressedItem()
{
	return selectedItemIndex;
}

void PauseScreen::run(sf::RenderWindow& gameWindow)
{
	pauseWindow.create(sf::VideoMode(800, 600), "Pause", sf::Style::Close | sf::Style::Titlebar);
	Menu menu(pauseWindow.getSize().x, pauseWindow.getSize().y);

	while (pauseWindow.isOpen())
	{
		sf::Event event;
		while (pauseWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				pauseWindow.close();
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
						pauseWindow.close();
						break;
					case 2:
						pauseWindow.close();
						gameWindow.close();
						menu.run();
						break;
					case 3:
						pauseWindow.close();
						gameWindow.close();
						break;
					}
				}
			}
		}
		pauseWindow.clear();
		draw(pauseWindow);
		pauseWindow.display();
	}
}
