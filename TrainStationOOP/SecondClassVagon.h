#pragma once
#include "BaseVagon.h"

class SecondClassVagon : public BaseVagon
{
private:
	unsigned int kgPrice;

public:

	SecondClassVagon(unsigned int basePrice, unsigned int kgPrice);
	unsigned int getKgPrice() const;

	unsigned int getPriceForSeat(unsigned int kgBaggage) const;
	void printUnoccupiedSeats() const override;

	BaseVagon* clone() const override;
};

