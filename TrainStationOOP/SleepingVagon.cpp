#include "SleepingVagon.h"
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
	for (size_t i = 0;i < tempConstants::NUMBER_OF_ROWS;i++) {
		std::cout << "| ";
		if (BaseVagon::getIsTaken(i, 0)) std::cout << "XX";
		else std::cout << std::setw(2) << std::setfill('0') << seat;

		std::cout << " |\n";
		seat++;
	}
	BaseVagon::printChar(tempConstants::FACTOR_FOR_OUTLINING);
}

BaseVagon* SleepingVagon::clone() const
{
	return new SleepingVagon(getBasePrice(), getHundredKilometersPrice());
}
