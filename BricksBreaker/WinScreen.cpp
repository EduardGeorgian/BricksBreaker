#include "WinScreen.h"



WinScreen::WinScreen(float width, float height)
{
	if (!font.loadFromFile("Resources/Fonturi/arial.ttf"))
	{
		std::cout << "Error loading font" << std::endl;	
	}
	winText.setFont(font);
	winText.setString("You Win!");
	winText.setCharacterSize(50);
	winText.setFillColor(sf::Color::White);
	winText.setPosition(sf::Vector2f(width / 2 - 100, height / 2 - 200));

	scoreText.setFont(font);
	scoreText.setString("Score: ");
	scoreText.setCharacterSize(30);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(sf::Vector2f(width / 2 - 100, height / 2 - 100));

	playAgainText.setFont(font);
	playAgainText.setString("Play Again");
	playAgainText.setCharacterSize(30);
	playAgainText.setFillColor(sf::Color::Red);
	playAgainText.setPosition(sf::Vector2f(width / 2 - 100, height / 2));

	exitText.setFont(font);
	exitText.setString("Exit");
	exitText.setCharacterSize(30);
	exitText.setFillColor(sf::Color::White);
	exitText.setPosition(sf::Vector2f(width / 2 - 100, height / 2 + 100));

	selectedItemIndex = 0;
}

bool WinScreen::run(sf::RenderWindow& window, bool isWin)
{
	setSound();
	if (isWin)
	{
		winText.setString("You Win!");
	}
	else
	{
		winText.setString("You Lose!");
	}
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					MoveUp();
					break;
				case sf::Keyboard::Down:
					MoveDown();
					break;
				case sf::Keyboard::Return:
					switch (GetPressedItem())
					{
					case 0:
						window.close();
						return true;
						break;
					case 1:
						window.close();
						return false;
						break;
					}
					break;
				}
				break;
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
		draw(window);
	}
	return false;	
}

void WinScreen::draw(sf::RenderWindow& window)
{
	window.clear();
	window.draw(winText);
	/*window.draw(scoreText);*/
	window.draw(playAgainText);
	window.draw(exitText);
	window.display();
}

void WinScreen::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		playSound();
		playAgainText.setFillColor(sf::Color::White);
		exitText.setFillColor(sf::Color::White);
		selectedItemIndex--;
		if (selectedItemIndex == 0)
		{
			playAgainText.setFillColor(sf::Color::Red);
		}
	}
}

void WinScreen::MoveDown()
{
	if (selectedItemIndex + 1 < 2)
	{
		playSound();
		playAgainText.setFillColor(sf::Color::White);
		exitText.setFillColor(sf::Color::White);
		selectedItemIndex++;
		if (selectedItemIndex == 1)
		{
			exitText.setFillColor(sf::Color::Red);
		}
	}
}

int WinScreen::GetPressedItem()
{
	return selectedItemIndex;
}

void WinScreen::setSound()
{
	if (!buffer.loadFromFile("Resources/Sounds/MenuSound.wav"))
	{
		std::cout << "Error loading menu sound file\n";
	}
	sound.setBuffer(buffer);
}

void WinScreen::playSound()
{
	sound.play();
}

