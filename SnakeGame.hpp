#pragma once

#include <memory>
#include "Utils.hpp"
#include "BWriter.hpp"

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 600

using Utils::Coords, Utils::Snake, Utils::Food;

namespace Game
{
	class SnakeGame
	{
		bool MAIN_MENU = true;
		bool GAME_OVER = false;

		Utils::BWriter bWriter;
		sf::Keyboard::Key lastKey;
		std::shared_ptr<Food> food;
		std::shared_ptr<Snake> head;
		std::shared_ptr<sf::RenderWindow> window;

		/**
		 * @return Coords
		 */
		inline Coords generateRandomCoords();

		// Initializes game variables
		inline void init();

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

		// Adds a new node to the Snake, starting from the head
		void addNode();

		// Verifies if a collision with maps limits or nodes happened
		void checkCollisions();

		/**
		 * Deals with gameplay events
		 * @param sf::Event &event
		 */
		void watchEvents(sf::Event &event);

	public:
		SnakeGame() = default;

		// Main function. Runs the game event loop
		void run();

		// Prints the GameOver screen
		void gameOver() noexcept(false);

	private: // MENU OPTIONS
		typedef struct MenuButton {
			sf::FloatRect bounds;
			std::string text;
		} MenuButton;

		enum MenuOptions
		{
			NEW_GAME,
			CONTINUE,
			EXIT
		};

		std::vector<MenuButton> buttons;

		/**
		 * Draws the menu window and watch for mouse button events
		 * @param sf::Event &event
		 */
		void dealWithMenuSelection(sf::Event &event);
	};
}
