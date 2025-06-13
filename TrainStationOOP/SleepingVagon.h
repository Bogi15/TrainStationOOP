#pragma once
#include "BaseVagon.h"

class SleepingVagon : public BaseVagon
{
private:
	unsigned int hundredKilometersPrice;

public:

	SleepingVagon() = default;
	SleepingVagon(unsigned int basePrice, unsigned int hundredKilometersPrice);
	unsigned int getHundredKilometersPrice() const;

	unsigned int getPriceForSeat(unsigned int distantce) const;

	void printUnoccupiedSeats() const override;
	BaseVagon* clone() const override;
	void buyPlaceOnSeat(size_t seat) override;
	void setSeats(const bool** seats) override;


	VagonType typeVagon() const override;
	void writeVagonBinary(std::ofstream& ofs) const override;
	void readVagonBinary(std::ifstream& ifs) override;

	String getTypeWagonString() const override;
	void printWagon() const override;
};

