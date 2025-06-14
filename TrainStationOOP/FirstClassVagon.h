#pragma once
#include "BaseVagon.h"


class FirstClassVagon : public BaseVagon
{
private:
	
	bool foodIncluded;
	double comfortFactor;

public:

	FirstClassVagon() = default;
	FirstClassVagon(unsigned int basePrice, double comfortFactor);
	unsigned int getPriceForSeat() const;
	bool getFoodIncluded() const;
	double getComforFactor() const;


	void printUnoccupiedSeats() const override;
	BaseVagon* clone() const override;
	void buyPlaceOnSeat(size_t seat) override;
	void setSeats(const bool** seats) override;

	VagonType typeVagon() const override;
	void writeVagonBinary(std::ofstream& ofs) const override;
	void readVagonBinary(std::ifstream& ifs) override;

	bool isFree(size_t seat)const override;
	bool wagonIsFree()const override;


	String getTypeWagonString() const override;
	void printWagon() const override;

};