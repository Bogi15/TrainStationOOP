#pragma once
#include "BaseVagon.h"

class SleepingVagon : public BaseVagon
{
private:
	unsigned int hundredKilometersPrice;

public:

	SleepingVagon(unsigned int basePrice, unsigned int hundredKilometersPrice);
	unsigned int getPriceForSeat(unsigned int distantce) const;
	void printUnoccupiedSeats() const override;
};

