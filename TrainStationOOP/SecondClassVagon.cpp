#include "SecondClassVagon.h"
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

unsigned int SecondClassVagon::getPriceForSeat(unsigned int kgBaggage) const
{
    return this->getBasePrice() + this->kgPrice * kgBaggage;
}

void SecondClassVagon::printUnoccupiedSeats() const
{
	BaseVagon::printChar(tempConstants::FACTOR_FOR_OUTLINING * tempConstants::NUMBER_OF_COLS - 1);
	size_t seat = 1;
	for (size_t i = 0;i < tempConstants::NUMBER_OF_ROWS;i++) {
		std::cout << "|";
		for (size_t j = 0;j < tempConstants::NUMBER_OF_COLS;j++) {
			if (BaseVagon::getIsTaken(i, j)) std::cout << "XX";
			else std::cout << std::setw(2) << std::setfill('0') << seat;

			if (j != tempConstants::NUMBER_OF_COLS - 1) std::cout << " ";
			seat++;
		}
		std::cout << "|\n";
	}
	BaseVagon::printChar(tempConstants::FACTOR_FOR_OUTLINING * tempConstants::NUMBER_OF_COLS - 1);
}

