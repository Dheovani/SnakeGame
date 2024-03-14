#pragma once

#include <vector>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Utils.hpp"

namespace Utils
{
	typedef struct Record {
		sf::Keyboard::Key direction;
		Utils::Food food;
		std::vector<Utils::Snake> snakeNodes;
	} Record;

	class BWriter final
	{
	public:
		BWriter();

		void write(Record value) const;

		Record read() const;

		void deleteRecords() const;

		std::vector<Utils::Snake> buildVector(std::shared_ptr<Snake> headNode);
	};
}
