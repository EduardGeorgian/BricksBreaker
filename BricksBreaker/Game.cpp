#include "Game.h"



Game::Game():paddle(),ball(),ballVelocity(200.f,200.f),paddleSpeed(400.f),movingLeft(false),
	movingRight(false),
	isPaused(false),
	isGameOver(false)
{
	paddle.setSize(sf::Vector2f(100, 20));
	paddle.setFillColor(::sf::Color::Red);
	paddle.setPosition(350, 550);

	ball.setRadius(10.f);
	ball.setFillColor(sf::Color::White);
	ball.setPosition(300, 300);

	float brickWidth = 70.f;
	float brickHeight = 20.f;
	float spacing = 10.f;
	int numBricksPerRow = 10;
	int numRows=5;


	//create bricks

	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numBricksPerRow; j++)
		{
			Brick brick;
			brick.shape.setSize(sf::Vector2f(brickWidth,brickHeight));
			brick.shape.setFillColor(sf::Color::Blue);
			brick.shape.setPosition(j*(brickWidth+spacing)+spacing,i*(brickHeight+spacing)+spacing);
			bricks.push_back(brick);
		}
	}

}


void Game::initWindow()
{
	gameWindow.create(sf::VideoMode(800, 600), "Bricks Breaker", sf::Style::Close | sf::Style::Titlebar);
	gameWindow.setFramerateLimit(60);
}


void Game::Run()
{
	initWindow();
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
			handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;

		default:
			break;
		}
		
	}
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::Left)
	{
		movingLeft = isPressed;
	}
	else if (key == sf::Keyboard::Right)
	{
		movingRight = isPressed;
	}
	else if (key == sf::Keyboard::P && isPressed)
	{
		isPaused = !isPaused; //inital isPaused este 0
	}
}


void Game::update(sf::Time deltaTime) {
	if (isPaused) {
		PauseScreen pauseScreen(this->gameWindow.getSize().x, this->gameWindow.getSize().y);
		pauseScreen.run(getWindow(), isPaused);
		isPaused = false;
		return;
	}

	sf::Vector2f movement(0.f, 0.f);
	if (movingLeft) {
		movement.x -= paddleSpeed;
	}
	if (movingRight) {
		movement.x += paddleSpeed;
	}

	paddle.move(movement * deltaTime.asSeconds());

	// make sure the paddle stays in window

	if (paddle.getPosition().x < 0.f) {
		paddle.setPosition(0.f, paddle.getPosition().y);
	}
	if (paddle.getPosition().x + paddle.getSize().x > gameWindow.getSize().x) {
		paddle.setPosition(gameWindow.getSize().x - paddle.getSize().x, paddle.getPosition().y);
	}

	ball.move(ballVelocity * deltaTime.asSeconds());

	if (ball.getPosition().x < 0.f || ball.getPosition().x + ball.getRadius() * 2 > gameWindow.getSize().x) {
		ballVelocity.x = -ballVelocity.x;
	}
	if (ball.getPosition().y < 0.f) {
		ballVelocity.y = -ballVelocity.y;
	}

	if (ball.getGlobalBounds().intersects(paddle.getGlobalBounds())) {
		ballVelocity.y = -ballVelocity.y;
		ball.setPosition(ball.getPosition().x, paddle.getPosition().y - ball.getRadius() * 2);
	}

	for (auto& brick : bricks) {
		if (brick.isDestroyed)
			continue;

		if (ball.getGlobalBounds().intersects(brick.shape.getGlobalBounds())) {
			brick.isDestroyed = true;
			ballVelocity.y = -ballVelocity.y;
		}
	}

	if (ball.getPosition().y > gameWindow.getSize().y) {
		gameWindow.close();
		Menu menu(gameWindow.getPosition().x, gameWindow.getPosition().y);
		menu.run();
		isGameOver = true;
	}
}


void Game::render()
{
	gameWindow.clear();
	gameWindow.draw(paddle);
	gameWindow.draw(ball);

	for (const auto& brick : bricks)
	{
		if (!brick.isDestroyed)
		{
			gameWindow.draw(brick.shape);
		}
	}
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