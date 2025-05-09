#pragma once
#include "BaseVagon.h"


class FirstClassVagon : public BaseVagon
{
private:
	
	bool foodIncluded;
	double confortFactor;

public:

	FirstClassVagon(unsigned int basePrice, double confortFactor);
	unsigned int getPriceForSeat() const;

	void printUnoccupiedSeats() const override;
};

