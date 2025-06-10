#pragma once
#include "BaseVagon.h"


class FirstClassVagon : public BaseVagon
{
private:
	
	bool foodIncluded;
	double comfortFactor;

public:

	FirstClassVagon(unsigned int basePrice, double comfortFactor);
	unsigned int getPriceForSeat() const;
	bool getFoodIncluded() const;
	double getComforFactor() const;


	void printUnoccupiedSeats() const override;
	BaseVagon* clone() const override;
};

