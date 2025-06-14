#pragma once
#include "BaseVagon.h"

class SecondClassVagon : public BaseVagon
{
private:
	unsigned int kgPrice;

public:

	SecondClassVagon() = default;
	SecondClassVagon(unsigned int basePrice, unsigned int kgPrice);
	unsigned int getKgPrice() const;

	unsigned int getPriceForSeat(unsigned int kgBaggage) const;

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

