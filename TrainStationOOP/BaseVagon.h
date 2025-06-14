#pragma once
#include "Vector.hpp"
#include "VagonType.h"
#include "String.h"

class BaseVagon
{
private:
	bool** seats;
	size_t seatRows;
	size_t seatCols;
	unsigned int ID;
	unsigned int basePrice;
	

	//static unsigned int nextID;

	void free();
	void copyFrom(const BaseVagon& other);
	void moveFrom(BaseVagon&& other) noexcept;
	

protected:
	BaseVagon(unsigned int basePrice, size_t rows, size_t cols);
	void printChar(size_t numberOfTimes) const;
public:

	BaseVagon() = default;
	BaseVagon(const BaseVagon& other);
	BaseVagon(BaseVagon&& other) noexcept;
	BaseVagon& operator=(const BaseVagon& other);
	BaseVagon& operator=(BaseVagon&& other) noexcept;
	virtual ~BaseVagon();
	virtual BaseVagon* clone() const = 0;

	unsigned int getBasePrice() const;
	unsigned int getWagonID()const;
	bool**& getSeats();
	const bool* const* getSeats() const;

	void setBasePrice(unsigned int price);
	void setWagonID(unsigned int wagonID);
	virtual void setSeats(const bool** seats) = 0;
	void setNextID(unsigned int lastWagonID);

	bool getIsTaken(size_t row, size_t col) const;
	virtual bool isFree(size_t seat)const = 0;
	void setIsTaken(size_t row, size_t col, bool state);
	virtual void printUnoccupiedSeats() const = 0;
	virtual void printWagon() const = 0;

	virtual VagonType typeVagon() const = 0;

	virtual void writeVagonBinary(std::ofstream& ofs) const;
	virtual void readVagonBinary(std::ifstream& ifs);
	

	virtual void buyPlaceOnSeat(size_t seat) = 0;
	virtual String getTypeWagonString() const = 0;
};

