#include "BWriter.hpp"
#include <fstream>
#include <iostream>

using Utils::BWriter, Utils::Record;

BWriter::BWriter()
{
	std::ofstream fout("records.dat", std::ios::binary | std::ios::app);
	fout.close();
}

void BWriter::write(Record value) const
{
	std::ofstream fout("records.dat", std::ios::binary | std::ios::app);

	if (fout) {
		fout.write(reinterpret_cast<char*>(&value), sizeof(value));
		fout.close();
	}
	else {
		std::cerr << "Error opening file!!" << std::endl;
	}
}

Record BWriter::read() const
{
	std::ifstream fin("records.dat", std::ios::binary | std::ios::in);

	if (fin) {
		Record record{};

		if (fin.read(reinterpret_cast<char*>(&record), sizeof(Record))) {
			fin.close();

			return record;
		}

		fin.close();
	}
	else {
		std::cerr << "Error opening file!!" << std::endl;
	}

	throw std::exception("Value not found!");
}

void BWriter::deleteRecords() const
{
	Record rec{};
	write(rec);
}

std::vector<Utils::Snake> BWriter::buildVector(std::shared_ptr<Snake> headNode)
{
	std::vector<Snake> snakes = { *headNode };
	std::shared_ptr<Snake> currentNode = headNode->node;

	while (currentNode != nullptr) {
		snakes.push_back(*currentNode);

		currentNode = currentNode->node;
	}

	return snakes;
}
