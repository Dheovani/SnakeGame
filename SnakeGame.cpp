#include "SnakeGame.hpp"
#include <random>
#include <thread>
#include <chrono>
#include <iostream>

using namespace Game;

inline Coords SnakeGame::generateRandomCoords()
{
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<size_t> distribution(5, 95);

	size_t y = distribution(generator) * 10;
	y = y > WINDOW_HEIGHT ? (y - WINDOW_HEIGHT) : y;

	Coords coord = { distribution(generator) * 10, y };
	return coord;
}

void SnakeGame::moveSnake(sf::Keyboard::Key key)
{
	lastKey = key;

	if (head->node != nullptr)
		updateNodeCoords(head->node, head->coords);

	if (head->coords == food->coords) {
		food->coords = generateRandomCoords();

		addNode();
	}

	switch (key) {
	case sf::Keyboard::Up:
		head->coords.y -= 10;

		break;
	case sf::Keyboard::Left:
		head->coords.x -= 10;

		break;
	case sf::Keyboard::Right:
		head->coords.x += 10;

		break;
	case sf::Keyboard::Down:
		head->coords.y += 10;

		break;
	}
}

void SnakeGame::updateNodeCoords(std::shared_ptr<Snake> node, const Coords &coords)
{
	if (node->node != nullptr)
		updateNodeCoords(node->node, node->coords);

	node->coords = coords;
}

void SnakeGame::drawSnake()
{
	sf::RectangleShape snake(sf::Vector2f(10, 10));
	snake.setFillColor(sf::Color::Green);

	std::shared_ptr<Snake> currentNode = head;

	do {
		snake.setPosition((float)currentNode->coords.x, (float)currentNode->coords.y);
		window->draw(snake);

		currentNode = currentNode->node;
	} while (currentNode != nullptr);
}

void SnakeGame::drawFood()
{
	sf::RectangleShape foodRec(sf::Vector2f(10, 10));
	foodRec.setFillColor(sf::Color::Red);
	foodRec.setPosition((float)food->coords.x, (float)food->coords.y);

	window->draw(foodRec);
}

std::shared_ptr<Snake> SnakeGame::addNode()
{
	head->size++;
	std::shared_ptr<Snake> currentNode = head;

	while (currentNode->node != nullptr)
		currentNode = currentNode->node;

	currentNode->node = std::make_shared<Snake>();
	currentNode->node->size = 1;
	currentNode->node->coords = currentNode->coords;
	currentNode->node->node = nullptr;

	return currentNode->node;
}

void SnakeGame::checkCollisions()
{
	if (head->coords.x == 0 || head->coords.x == WINDOW_WIDTH ||
		head->coords.y == 0 || head->coords.y == WINDOW_HEIGHT)
	{
		GAME_OVER = true;
		return;
	}

	std::shared_ptr<Snake> currentNode = head->node;

	while (currentNode != nullptr) {
		if (currentNode->coords == head->coords) {
			GAME_OVER = true;
			return;
		}

		currentNode = currentNode->node;
	}
}

void SnakeGame::watchEvents(sf::Event &event)
{
	while (window->pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			window->close();

			break;
		case sf::Event::KeyPressed:
			moveSnake(event.key.code);

			break;
		}
	}

	moveSnake(lastKey);
	std::this_thread::sleep_for(std::chrono::milliseconds(30));
}

SnakeGame::SnakeGame()
{
	head = std::make_shared<Snake>();
	head->size = 1;
	head->coords = generateRandomCoords();
	head->node = nullptr;

	food = std::make_shared<Food>();
	food->coords = generateRandomCoords();

	// Moves right by default
	lastKey = sf::Keyboard::Right;

	window = std::make_shared<sf::RenderWindow>(
		sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
		"Snake Game",
		sf::Style::Titlebar | sf::Style::Close);
}

void SnakeGame::run()
{
	while (window->isOpen()) {
		sf::Event event;

		if (GAME_OVER) {
			gameOver();

			if (window->pollEvent(event) &&
				event.type == sf::Event::KeyPressed &&
				event.key.code == sf::Keyboard::Enter)
			{
				head->size = 1;
				head->node = nullptr;
				head->coords = generateRandomCoords();

				food->coords = generateRandomCoords();

				GAME_OVER = false;
			}

			continue;
		}
		
		watchEvents(event);
		checkCollisions();

		window->clear(sf::Color::Black);
		drawFood();
		drawSnake();
		window->display();
	}
}

void SnakeGame::gameOver()
{
	GAME_OVER = true;

	sf::Font font;
	if (!font.loadFromFile("font.ttf")) {
		throw "Failed loading font!!";
	}

	sf::Text gameOverText("Game Over", font, 50),
		sub("Press \"Enter\" to go back to play again", font, 20);
	sf::FloatRect textBounds = gameOverText.getLocalBounds();

	unsigned int windowWidth = window->getSize().x;
	unsigned int windowHeight = window->getSize().y;

	gameOverText.setFillColor(sf::Color::Red);
	gameOverText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
	gameOverText.setPosition(windowWidth / 2.0f, windowHeight / 2.3f);

	textBounds = sub.getLocalBounds();
	sub.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
	sub.setPosition(windowWidth / 2.0f, windowHeight / 1.8f);

	window->clear(sf::Color::Black);
	window->draw(gameOverText);
	window->draw(sub);
	window->display();
}
