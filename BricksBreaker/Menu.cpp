#include "Menu.h"


Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("D:/C++Games/BricksBreaker/BricksBreaker/Fonturi/arial.ttf"))
	{
		std::cout << "Error loading font" << std::endl;
	}
	// Set the font of the menu items
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Play");
	menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Options");
	menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Exit");
	menu[2].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 3)); 

	selectedItemIndex = 0; // Set the default selected item to 0
	setSound();
}	

void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}


void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

int Menu::GetPressedItem()
{
	return selectedItemIndex;
}



void Menu::run()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Bricks Breaker", sf::Style::Close | sf::Style::Titlebar);
	Menu menu(window.getSize().x, window.getSize().y);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Up) {
					menu.MoveUp();
					playSound();
					
				}
				else if (event.key.code == sf::Keyboard::Down) {
					menu.MoveDown();
					playSound();
					
				}
				else if (event.key.code == sf::Keyboard::Return) {
					int selectedItem = menu.GetPressedItem();
					if (selectedItem == 0) {
						window.close();
						Game game;
						game.Run();
					}
					else if (selectedItem == 1) {
						window.close();
						Instructions instructions(window.getSize().x, window.getSize().y);
						instructions.run();
					}
					else if (selectedItem == 2) {
						window.close();
					}
				}
			}
		}

		window.clear();
		menu.draw(window);
		window.display();
	}
}


void Menu::setSound()
{
	if (!buffer.loadFromFile("D:/C++Games/BricksBreaker/BricksBreaker/Sounds/MenuSound.wav"))
	{
		std::cout << "Error loading sound" << std::endl;
	}
	sound.setBuffer(buffer);
	sound.setVolume(50);
}

void Menu::playSound()
{
	sound.play();
}

void Menu::stopSound()
{
	sound.stop();
}

