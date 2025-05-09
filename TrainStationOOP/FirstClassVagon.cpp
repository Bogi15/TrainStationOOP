#include "FirstClassVagon.h"
#include <iostream>
#include <iomanip>

namespace tempConstants {
	constexpr int FACTOR_FOR_OUTLINING = 3;
	constexpr int PRICE_TO_INCLUDE_FOOD = 10;
	constexpr int NUMBER_OF_ROWS = 5;
	constexpr int NUMBER_OF_COLS = 2;
}

FirstClassVagon::FirstClassVagon(unsigned int basePrice, double confortFactor) : BaseVagon(basePrice,tempConstants::NUMBER_OF_ROWS, tempConstants::NUMBER_OF_COLS)
{
	this->confortFactor = confortFactor;
}

unsigned int FirstClassVagon::getPriceForSeat() const
{
	return this->getBasePrice() * this->confortFactor + (foodIncluded) ? tempConstants::PRICE_TO_INCLUDE_FOOD : 0;
}

void FirstClassVagon::printUnoccupiedSeats() const
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
