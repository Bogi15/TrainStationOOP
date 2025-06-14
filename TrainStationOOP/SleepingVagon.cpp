#include "SleepingVagon.h"
#include "String.h"
#include <iostream>
#include <iomanip>

namespace tempConstants {
	constexpr int FACTOR_FOR_OUTLINING = 4;
	constexpr int NUMBER_OF_ROWS = 5;
	constexpr int NUMBER_OF_COLS = 1;
}

SleepingVagon::SleepingVagon(unsigned int basePrice, unsigned int hundredKilometersPrice) : BaseVagon(basePrice, tempConstants::NUMBER_OF_ROWS, tempConstants::NUMBER_OF_COLS)
{
	this->hundredKilometersPrice = hundredKilometersPrice;
}

unsigned int SleepingVagon::getHundredKilometersPrice() const
{
	return this->hundredKilometersPrice;
}

unsigned int SleepingVagon::getPriceForSeat(unsigned int distantce) const
{
	return this->getBasePrice() + (this->hundredKilometersPrice / 100) * distantce;
}

void SleepingVagon::printUnoccupiedSeats() const
{	
	BaseVagon::printChar(tempConstants::FACTOR_FOR_OUTLINING);
	size_t seat = 1;
	for (size_t i = 0;i < tempConstants::NUMBER_OF_ROWS * 2;i++) {
		if (i % 2 == 0) {
			std::cout << "| ";
			if (BaseVagon::getIsTaken(i/2, 0)) std::cout << "XX";
			else std::cout << std::setw(2) << std::setfill('0') << seat;

			std::cout << " |\n";
			seat++;
		}
		else std::cout << "|    |\n";
	}
	BaseVagon::printChar(tempConstants::FACTOR_FOR_OUTLINING);
}

BaseVagon* SleepingVagon::clone() const
{
	return new SleepingVagon(*this);
}

void SleepingVagon::buyPlaceOnSeat(size_t seat)
{

	if (seat == 0 || seat > tempConstants::NUMBER_OF_COLS * tempConstants::NUMBER_OF_ROWS) {
		throw std::out_of_range("Invalid seat number");
	}

	seat--;

	size_t row = seat / tempConstants::NUMBER_OF_COLS;
	size_t col = seat % tempConstants::NUMBER_OF_COLS;

	if (BaseVagon::getIsTaken(row, col)) {
		throw std::runtime_error("The seat is taken");
	}
	BaseVagon::setIsTaken(row, col, true);
}

void SleepingVagon::setSeats(const bool** seats)
{
	for (size_t i = 0;i < tempConstants::NUMBER_OF_ROWS;i++) {
		for (size_t j = 0;j < tempConstants::NUMBER_OF_COLS;j++) {
			getSeats()[i][j] = seats[i][j];
		}
	}
}

bool SleepingVagon::isFree(size_t seat) const
{
	if (seat == 0 || seat > tempConstants::NUMBER_OF_COLS * tempConstants::NUMBER_OF_ROWS) {
		throw std::out_of_range("Invalid seat number");
	}

	seat--;

	size_t row = seat / tempConstants::NUMBER_OF_COLS;
	size_t col = seat % tempConstants::NUMBER_OF_COLS;

	if (BaseVagon::getIsTaken(row, col)) {
		throw std::runtime_error("The seat is taken");
	}

	return true;
}

bool SleepingVagon::wagonIsFree() const
{
	for (size_t i = 0;i < tempConstants::NUMBER_OF_ROWS;i++) {
		for (size_t j = 0;j < tempConstants::NUMBER_OF_COLS;j++) {
			if (getIsTaken(i,j)) return false;
		}
	}

	return true;
}

VagonType SleepingVagon::typeVagon() const
{
	return VagonType::sleeping;
}

void SleepingVagon::writeVagonBinary(std::ofstream& ofs) const
{
	BaseVagon::writeVagonBinary(ofs);

	ofs.write((const char*)&hundredKilometersPrice, sizeof(unsigned int));
}

void SleepingVagon::readVagonBinary(std::ifstream& ifs)
{
	BaseVagon::readVagonBinary(ifs);

	ifs.read((char*)&hundredKilometersPrice, sizeof(unsigned int));
}

String SleepingVagon::getTypeWagonString() const
{
	return "Sleeping Class";
}

void SleepingVagon::printWagon() const
{
	std::cout << "===Wagon ID: " << getWagonID() << "===" << std::endl;
	std::cout << "Wagon Type: " << getTypeWagonString() << std::endl;
	std::cout << "Base price: " << getBasePrice() << " lv." << std::endl;
	std::cout << "Price for 100 km : " << hundredKilometersPrice << " lv." << std::endl;
	std::cout << "Seats: " << tempConstants::NUMBER_OF_COLS * tempConstants::NUMBER_OF_ROWS << std::endl;
	std::cout << "Available Seats:" << std::endl;
	printUnoccupiedSeats();
	std::cout << std::endl;
}
