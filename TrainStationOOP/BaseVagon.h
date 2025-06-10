#pragma once
class BaseVagon
{
private:
	bool** seats;
	size_t seatRows;
	size_t seatCols;
	unsigned int ID;
	unsigned int basePrice;

	static unsigned int nextID;

	void free();
	void copyFrom(const BaseVagon& other);
	void moveFrom(BaseVagon&& other);
	

protected:
	BaseVagon(unsigned int basePrice, size_t rows, size_t cols);
	void printChar(size_t numberOfTimes) const;
public:

	BaseVagon() = default;
	BaseVagon(const BaseVagon& other);
	BaseVagon(BaseVagon&& other);
	BaseVagon& operator=(const BaseVagon& other);
	BaseVagon& operator=(BaseVagon&& other);
	virtual ~BaseVagon();
	virtual BaseVagon* clone() const = 0;

	unsigned int getBasePrice() const;
	bool getIsTaken(size_t row, size_t col) const;
	virtual void printUnoccupiedSeats() const = 0;
	unsigned int getVagonID()const;
};

