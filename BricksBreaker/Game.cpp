#include "Game.h"



Game::Game()
{
	initWindow();
}


void Game::initWindow()
{
	gameWindow.create(sf::VideoMode(800, 600), "Bricks Breaker", sf::Style::Close | sf::Style::Titlebar);
	gameWindow.setFramerateLimit(60);
}


void Game::Run()
{
    sf::Clock clock;
    while (gameWindow.isOpen()) {
        sf::Time deltaTime = clock.restart();
        processEvents();
        update(deltaTime);
        render();
    }
}

void Game::processEvents()
{
	sf::Event event;
	while (gameWindow.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			gameWindow.close();
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape) {
				gameWindow.close();
			}
			if (event.key.code == sf::Keyboard::P)
			{
				PauseScreen pauseScreen(this->gameWindow.getSize().x,this->gameWindow.getSize().y);
				pauseScreen.run(getWindow());
			}
			break;

		default:
			break;
		}
		
	}
}

void Game::update(sf::Time deltaTime)
{
}

void Game::render()
{
	gameWindow.clear();
	gameWindow.display();
}

sf::RenderWindow& Game::getWindow()
{
	return gameWindow;
}
void Game::Close()
{
	gameWindow.close();
}