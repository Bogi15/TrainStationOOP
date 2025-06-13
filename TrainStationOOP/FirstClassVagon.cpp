#include "FirstClassVagon.h"
#include "String.h"
#include <iostream>
#include <iomanip>

namespace tempConstants {
	constexpr int FACTOR_FOR_OUTLINING = 3;
	constexpr int PRICE_TO_INCLUDE_FOOD = 10;
	constexpr int NUMBER_OF_ROWS = 5;
	constexpr int NUMBER_OF_COLS = 2;
}

FirstClassVagon::FirstClassVagon(unsigned int basePrice, double comfortFactor) : BaseVagon(basePrice,tempConstants::NUMBER_OF_ROWS, tempConstants::NUMBER_OF_COLS)
{
	this->comfortFactor = comfortFactor;
}

unsigned int FirstClassVagon::getPriceForSeat() const
{
	return this->getBasePrice() * this->comfortFactor + (foodIncluded) ? tempConstants::PRICE_TO_INCLUDE_FOOD : 0;
}

bool FirstClassVagon::getFoodIncluded() const
{
	return this->foodIncluded;
}

double FirstClassVagon::getComforFactor() const
{
	return this->comfortFactor;
}

void FirstClassVagon::printUnoccupiedSeats() const
{

	BaseVagon::printChar(tempConstants::FACTOR_FOR_OUTLINING * tempConstants::NUMBER_OF_COLS - 1);
	size_t seat = 1;
	for (size_t i = 0;i < tempConstants::NUMBER_OF_ROWS * 2;i++) {
		if (i % 2 == 0) {
			std::cout << "|";
			for (size_t j = 0;j < tempConstants::NUMBER_OF_COLS;j++) {
				if (BaseVagon::getIsTaken(i / 2, j)) std::cout << "XX";
				else std::cout << std::setw(2) << std::setfill('0') << seat;

				if (j != tempConstants::NUMBER_OF_COLS - 1) std::cout << " ";
				seat++;
			}
			std::cout << "|\n";
		}
		else std::cout << "|     |\n";
	}
	BaseVagon::printChar(tempConstants::FACTOR_FOR_OUTLINING * tempConstants::NUMBER_OF_COLS - 1);
}

BaseVagon* FirstClassVagon::clone() const
{
	return new FirstClassVagon(*this);
}

void FirstClassVagon::buyPlaceOnSeat(size_t seat)
{

	if (seat == 0 || seat > tempConstants::NUMBER_OF_COLS * tempConstants::NUMBER_OF_ROWS) {
		throw std::out_of_range("Invalid seat number");
	}

	seat--;

	size_t row = seat / tempConstants::NUMBER_OF_COLS;
	size_t col = seat % tempConstants::NUMBER_OF_COLS;

	if (BaseVagon::getIsTaken(row, col)) {
		throw std::runtime_error("Seat is already taken");
	}
	BaseVagon::setIsTaken(row, col, true);

}

void FirstClassVagon::setSeats(const bool** seats)
{
	for (size_t i = 0;i < tempConstants::NUMBER_OF_ROWS;i++) {
		for (size_t j = 0;j < tempConstants::NUMBER_OF_COLS;j++) {
			getSeats()[i][j] = seats[i][j];
		}
	}
}

VagonType FirstClassVagon::typeVagon() const
{
	return VagonType::firstClass;
}

void FirstClassVagon::writeVagonBinary(std::ofstream& ofs) const
{
	BaseVagon::writeVagonBinary(ofs);
	ofs.write((const char*)&foodIncluded, sizeof(bool));
	ofs.write((const char*)&comfortFactor, sizeof(double));
}

void FirstClassVagon::readVagonBinary(std::ifstream& ifs)
{
	BaseVagon::readVagonBinary(ifs);
	ifs.read((char*)&foodIncluded, sizeof(bool));
	ifs.read((char*)&comfortFactor, sizeof(double));
}

String FirstClassVagon::getTypeWagonString() const
{
	return "First Class";
}

void FirstClassVagon::printWagon() const
{
	std::cout << "===Wagon ID: " << getWagonID() << "===" << std::endl;
	std::cout << "Wagon Type: " << getTypeWagonString() << std::endl;
	std::cout << "Base price: " << getBasePrice() << " lv." << std::endl;
	std::cout << "Comfort Factor: " << comfortFactor << std::endl;
	std::cout << "Seats: " << tempConstants::NUMBER_OF_COLS * tempConstants::NUMBER_OF_ROWS << std::endl;
	std::cout << "Available Seats:" << std::endl;
	printUnoccupiedSeats();
	std::cout << std::endl;

}

