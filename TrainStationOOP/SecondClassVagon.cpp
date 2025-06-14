#include "SecondClassVagon.h"
#include "String.h"
#include <iostream>
#include <iomanip>

namespace tempConstants {
	constexpr int FACTOR_FOR_OUTLINING = 3;
	constexpr int NUMBER_OF_ROWS = 5;
	constexpr int NUMBER_OF_COLS = 4;
}

SecondClassVagon::SecondClassVagon(unsigned int basePrice, unsigned int kgPrice) : BaseVagon(basePrice, tempConstants::NUMBER_OF_ROWS, tempConstants::NUMBER_OF_COLS)
{
    this->kgPrice = kgPrice;
}

unsigned int SecondClassVagon::getKgPrice() const
{
	return this->kgPrice;
}

unsigned int SecondClassVagon::getPriceForSeat(unsigned int kgBaggage) const
{
    return this->getBasePrice() + this->kgPrice * kgBaggage;
}

void SecondClassVagon::printUnoccupiedSeats() const
{
	BaseVagon::printChar(tempConstants::FACTOR_FOR_OUTLINING * tempConstants::NUMBER_OF_COLS - 1);
	size_t seat = 1;
	for (size_t i = 0;i < tempConstants::NUMBER_OF_ROWS * 2;i++) {
		if (i % 2 == 0) {
			std::cout << "|";
			for (size_t j = 0;j < tempConstants::NUMBER_OF_COLS;j++) {
				if (BaseVagon::getIsTaken(i/2, j)) std::cout << "XX";
				else std::cout << std::setw(2) << std::setfill('0') << seat;

				if (j != tempConstants::NUMBER_OF_COLS - 1) std::cout << " ";
				seat++;
			}
			std::cout << "|\n";
		}
		else std::cout << "|           |\n";
	}
	BaseVagon::printChar(tempConstants::FACTOR_FOR_OUTLINING * tempConstants::NUMBER_OF_COLS - 1);
}

BaseVagon* SecondClassVagon::clone() const
{
	return new SecondClassVagon(*this);
}

void SecondClassVagon::buyPlaceOnSeat(size_t seat)
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

void SecondClassVagon::setSeats(const bool** seats)
{
	for (size_t i = 0;i < tempConstants::NUMBER_OF_ROWS;i++) {
		for (size_t j = 0;j < tempConstants::NUMBER_OF_COLS;j++) {
			getSeats()[i][j] = seats[i][j];
		}
	}
}

VagonType SecondClassVagon::typeVagon() const
{
	return VagonType::secondClass;
}

void SecondClassVagon::writeVagonBinary(std::ofstream& ofs) const
{
	BaseVagon::writeVagonBinary(ofs);
	ofs.write((const char*)&kgPrice, sizeof(unsigned int));
}

void SecondClassVagon::readVagonBinary(std::ifstream& ifs)
{
	BaseVagon::readVagonBinary(ifs);
	ifs.read((char*)&kgPrice, sizeof(unsigned int));
}

bool SecondClassVagon::isFree(size_t seat) const
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

bool SecondClassVagon::wagonIsFree() const
{
	for (size_t i = 0;i < tempConstants::NUMBER_OF_ROWS;i++) {
		for (size_t j = 0;j < tempConstants::NUMBER_OF_COLS;j++) {
			if (getIsTaken(i, j)) return false;
		}
	}

	return true;
}

String SecondClassVagon::getTypeWagonString() const
{
	return "Second Class";
}

void SecondClassVagon::printWagon() const
{
	std::cout << "===Wagon ID: " << getWagonID() << "===" << std::endl;
	std::cout << "Wagon Type: " << getTypeWagonString() << std::endl;
	std::cout << "Base price: " << getBasePrice() << " lv." << std::endl;
	std::cout << "Price for 1 kg luggage: " << kgPrice << std::endl;
	std::cout << "Seats: " << tempConstants::NUMBER_OF_COLS * tempConstants::NUMBER_OF_ROWS << std::endl;
	std::cout << "Available Seats:" << std::endl;
	printUnoccupiedSeats();
	std::cout << std::endl;
}

