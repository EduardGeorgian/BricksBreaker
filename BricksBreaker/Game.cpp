#include "Game.h"



Game::Game():paddle(),ball(),ballVelocity(200.f,200.f),paddleSpeed(400.f),movingLeft(false),
	movingRight(false),
	isPaused(false),
	isGameOver(false),
	isWin(false),
	score(0),
	bonusActive(false),
	distribution(1, 3),
	generator(std::random_device()()),
	fallingBonusVelocity(0.f, 150.f)
{
	if (!paddleTexture.loadFromFile("Resources/Textures/PaddleTexture.jpg"))
	{
		std::cout << "Error loading paddle texture\n";
	}
	paddleTexture.setSmooth(true);
	paddle.setTexture(&paddleTexture);
	paddle.setSize(sf::Vector2f(100, 20));
	/*paddle.setFillColor(::sf::Color::Red);*/
	paddle.setPosition(350, 550);


	if (!ballTexture.loadFromFile("Resources/Textures/BallTexture.jpg"))
	{
		std::cout << "Error loading ball texture\n";
	}
	ballTexture.setSmooth(true);
	ballTexture.setRepeated(true);
	ball.setTexture(&ballTexture);
	ball.setRadius(15.f);
	/*ball.setFillColor(sf::Color::White);*/
	ball.setPosition(300, 300);


	float brickWidth = 70.f;
	float brickHeight = 20.f;
	float spacing = 10.f;
	int numBricksPerRow = 1;
	int numRows=1;
	totalBricks = numBricksPerRow * numRows;

	//create bricks

	if (!brickTexture.loadFromFile("Resources/Textures/BrickTexture.jpg"))
	{
		std::cout << "Error loading brick texture\n";
	}
	brickTexture.setSmooth(true);
	brickTexture.setRepeated(true);

	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numBricksPerRow; j++)
		{
			Brick brick;
			brick.shape.setTexture(&brickTexture);
			brick.shape.setSize(sf::Vector2f(brickWidth,brickHeight));
			/*brick.shape.setFillColor(sf::Color::Blue);*/
			brick.shape.setPosition(j*(brickWidth+spacing)+spacing,i*(brickHeight+spacing)+5*spacing);
			bricks.push_back(brick);
		}
	}

	
	setSounds();

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
	initScore();
	initFallingBonus();

	
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


//void Game::update(sf::Time deltaTime) {
//	if (isPaused) {
//		PauseScreen pauseScreen(this->gameWindow.getSize().x, this->gameWindow.getSize().y);
//		pauseScreen.run(getWindow(), isPaused);
//		isPaused = false;
//		return;
//	}
//	if (isGameOver)
//	{
//		gameWindow.clear();
//		gameWindow.close();
//		LossScreen lossScreen(this->gameWindow.getSize().x, this->gameWindow.getSize().y);
//		lossScreen.run(gameWindow, isGameOver);
//		return;
//	}
//
//	sf::Vector2f movement(0.f, 0.f);
//	if (movingLeft) {
//		movement.x -= paddleSpeed;
//	}
//	if (movingRight) {
//		movement.x += paddleSpeed;
//	}
//
//	paddle.move(movement * deltaTime.asSeconds());
//
//	// make sure the paddle stays in window
//
//	if (paddle.getPosition().x < 0.f) {
//		paddle.setPosition(0.f, paddle.getPosition().y);
//	}
//	if (paddle.getPosition().x + paddle.getSize().x > gameWindow.getSize().x) {
//		paddle.setPosition(gameWindow.getSize().x - paddle.getSize().x, paddle.getPosition().y);
//	}
//
//	ball.move(ballVelocity * deltaTime.asSeconds());
//
//	if (ball.getPosition().x < 0.f || ball.getPosition().x + ball.getRadius() * 2 > gameWindow.getSize().x) {
//		ballVelocity.x = -ballVelocity.x;
//	}
//	if (ball.getPosition().y < 0.f) {
//		ballVelocity.y = -ballVelocity.y;
//	}
//
//	if (ball.getGlobalBounds().intersects(paddle.getGlobalBounds())) {
//		ballVelocity.y = -ballVelocity.y;
//		ball.setPosition(ball.getPosition().x, paddle.getPosition().y - ball.getRadius() * 2);
//	}
//
//	for (auto& brick : bricks) {
//		if (brick.isDestroyed)
//			continue;
//
//		if (ball.getGlobalBounds().intersects(brick.shape.getGlobalBounds())) {
//			brick.isDestroyed = true;
//			ballVelocity.y = -ballVelocity.y;
//		}
//	}
//
//	if (ball.getPosition().y > gameWindow.getSize().y) {
//		isGameOver = true;
//	}
//}
void Game::update(sf::Time deltaTime) {

	if (isPaused) {
		PauseScreen pauseScreen(this->gameWindow.getSize().x, this->gameWindow.getSize().y);
		if (pauseScreen.run(getWindow())) {
			isPaused = false;
		}
		else {
			isPaused = true;
		}
		return;
	}

	if (isGameOver) {
		gameWindow.clear();
		gameWindow.close();
		LossScreen lossScreen(this->gameWindow.getSize().x, this->gameWindow.getSize().y);
		lossScreen.run(gameWindow, isGameOver);
		return;
	}

	if (isWin)
	{
		WinScreen winScreen(this->gameWindow.getSize().x, this->gameWindow.getSize().y);
		if(winScreen.run(gameWindow, isWin)==true)
		{
			isWin = false;
			gameWindow.close();
			Game game;
			game.Run();
		}
		return;
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		isWin = true;
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

	if (!isPaused) {
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
			playPaddleHitSound();
		}

		for (auto& brick : bricks) {
			if (brick.isDestroyed)
				continue;

			if (ball.getGlobalBounds().intersects(brick.shape.getGlobalBounds())) {
				brick.isDestroyed = true;
				totalBricks--;
				if (totalBricks == 0)
				{
					isWin = true;
				}
				ballVelocity.y = -ballVelocity.y;
				updateScore();
				playBrickHitSound();
				if (!bonusActive && (distribution(generator) == 1))
				{
					bonusActive = true;
					fallingBonus.setPosition(brick.shape.getPosition());
				}
			}
		}

		if (fallingBonus.getPosition().y + fallingBonus.getRadius() * 2 > gameWindow.getSize().y)
		{
			resetFallingBonus();
		}

		if (bonusActive)
		{
			fallingBonus.move(fallingBonusVelocity * deltaTime.asSeconds());

			if (fallingBonus.getGlobalBounds().intersects(paddle.getGlobalBounds()))
			{
				playBonusHitSound();
				updateScore();
				resetFallingBonus();
			}
		}

		if (ball.getPosition().y > gameWindow.getSize().y) {
			isGameOver = true;
		}
	}
}



void Game::render()
{
	gameWindow.clear();
	gameWindow.draw(paddle);
	gameWindow.draw(ball);;
	
	

	for (const auto& brick : bricks)
	{
		if (!brick.isDestroyed)
		{
			gameWindow.draw(brick.shape);
		}
	}
	if(bonusActive)
	drawFallingBonus(gameWindow);

	drawScore(gameWindow);
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


void Game::initScore()
{
	if (!font.loadFromFile("Resources/Fonturi/arial.ttf"))
	{
		std::cout << "Error loading font\n";
	}
	scoreText.setFont(font);
	scoreText.setCharacterSize(24);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(10, 10);
	score = 0;
}

void Game::drawScore(sf::RenderWindow& gameWindow)
{
	scoreText.setString("Score: " + std::to_string(score));
	gameWindow.draw(scoreText);
}

void Game::updateScore()
{
	score += 10;
}


void Game::initFallingBonus()
{
	if (!fallingBonusTexture.loadFromFile("Resources/Textures/BonusTexture.png"))
	{
		std::cout << "Error loading bonus texture\n";
	}
	fallingBonusTexture.setSmooth(true);
	fallingBonus.setTexture(&fallingBonusTexture);
	fallingBonus.setRadius(20.f);
	/*fallingBonus.setFillColor(sf::Color::Green);*/
	resetFallingBonus();
}

void Game::drawFallingBonus(sf::RenderWindow& gameWindow)
{
	gameWindow.draw(fallingBonus);
}

void Game::resetFallingBonus()
{
	bonusActive = false;
	fallingBonus.setPosition(-100, -100);
}


void Game::setSounds()
{
	if (!paddleHitBuffer.loadFromFile("Resources/Sounds/PaddleHitSound.wav"))
	{
		std::cout << "Error loading paddle hit sound\n";
	}
	if (!brickHitBuffer.loadFromFile("Resources/Sounds/BrickHitSound.mp3"))
	{
		std::cout << "Error loading brick hit sound\n";
	}
	if (!bonusHitBuffer.loadFromFile("Resources/Sounds/BonusHitSound.mp3"))
	{
		std::cout << "Error loading bonus hit sound\n";
	}
	paddleHitSound.setBuffer(paddleHitBuffer);
	brickHitSound.setBuffer(brickHitBuffer);
	bonusHitSound.setBuffer(bonusHitBuffer);
	paddleHitSound.setVolume(50);
	brickHitSound.setVolume(50);
	bonusHitSound.setVolume(50);
}

void Game::playPaddleHitSound()
{
	paddleHitSound.play();
}

void Game::playBrickHitSound()
{
	brickHitSound.play();
}

void Game::playBonusHitSound()
{
	bonusHitSound.play();
}


