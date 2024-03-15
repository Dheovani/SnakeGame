#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 600

namespace Game
{
	typedef struct Coords
	{
		size_t x, y;

		// Assignment operator overload
		void operator=(const Coords& newCoords)
		{
			x = newCoords.x;
			y = newCoords.y;
		}

		// Comparisson operator overload
		bool operator==(const Coords& newCoords) const
		{
			return x == newCoords.x && y == newCoords.y;
		}
	} Coords;

	typedef struct Snake
	{
		size_t size;
		Coords coords;
		std::shared_ptr<Snake> node;
	} Snake;

	typedef struct Food
	{
		Coords coords;
	} Food;

	class SnakeGame
	{
		bool GAME_OVER = false;

		sf::Keyboard::Key lastKey;
		std::shared_ptr<Food> food;
		std::shared_ptr<Snake> head;
		std::shared_ptr<sf::RenderWindow> window;

		/**
		 * @return Coords
		 */
		inline Coords generateRandomCoords();

		/**
		 * Defines the position of the snake in the map
		 * @param sf::Keyboard::Key key
		 */
		void moveSnake(sf::Keyboard::Key key);

		/**
		 * Updates the snake's nodes coordinates
		 * @param std::shared_ptr<Snake> node
		 * @param const Coords &coords
		 */
		void updateNodeCoords(std::shared_ptr<Snake> node, const Coords &coords);

		// Draws the snake - starting from it's head up to it's last node - in the map
		void drawSnake();

		// Draw the food in the map
		void drawFood();

		/**
		 * Adds a new node to the Snake, starting from the head
		 * @return std::shared_ptr<Snake> - the new node
		 */
		std::shared_ptr<Snake> addNode();

		// Verifies if a collision with maps limits or nodes happened
		void checkCollisions();

		/**
		 * Deals with gameplay events
		 * @param sf::Event &event
		 */
		void watchEvents(sf::Event &event);

	public:
		// Initializes game's variables
		void init();

		// Main function. Runs the game event loop
		void run();

		// Prints the GameOver screen
		void gameOver() noexcept(false);
	};
}
