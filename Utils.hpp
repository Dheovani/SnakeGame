#pragma once

#include <memory>

namespace Utils
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
}
