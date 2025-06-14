#include "BaseVagon.h"
#include <iostream>
#include <iomanip>
#include <utility>
#include <exception>


//unsigned int BaseVagon::nextID = 1;

void BaseVagon::free()
{
	for (size_t i = 0;i < this->seatRows;i++) {
		delete[] seats[i];
	}
	delete[] seats;
	seats = nullptr;
}

void BaseVagon::copyFrom(const BaseVagon& other)
{
	this->seatRows = other.seatRows;
	this->seatCols = other.seatCols;
	this->ID = other.ID;
	this->basePrice = other.basePrice;
	
	this->seats = new bool*[this->seatRows];
	for (size_t i = 0;i < this->seatRows;i++) {
		this->seats[i] = new bool[seatCols];
	}

	for (size_t i = 0;i < this->seatRows;i++) {
		for (size_t j = 0;j < this->seatCols;j++) {
			this->seats[i][j] = other.seats[i][j];
		}
	}
}

void BaseVagon::moveFrom(BaseVagon&& other) noexcept
{
	this->seatRows = other.seatRows;
	this->seatCols = other.seatCols;
	//this->ID = BaseVagon::nextID++;
	this->basePrice = other.basePrice;


	this->seats = other.seats;
	other.seats = nullptr;
}

void BaseVagon::printChar(size_t numberOfTimes) const
{
	std::cout << ' ';
	for (size_t i = 0;i < numberOfTimes;i++) {
		std::cout << "-";
	}
	std::cout << " \n";
}

BaseVagon::BaseVagon(unsigned int basePrice, size_t rows, size_t cols)
{
	this->basePrice = basePrice;
	this->seatRows = rows;
	this->seatCols = cols;

	seats = new bool* [this->seatRows];
	for (size_t i = 0;i < this->seatRows;i++) {
		seats[i] = new bool[this->seatCols];
		for (size_t j = 0;j < this->seatCols;j++) {
			seats[i][j] = false;
		}
	}

}

BaseVagon::BaseVagon(const BaseVagon& other)
{
	copyFrom(other);
}

BaseVagon::BaseVagon(BaseVagon&& other) noexcept
{
	moveFrom(std::move(other));
}

BaseVagon& BaseVagon::operator=(const BaseVagon& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

BaseVagon& BaseVagon::operator=(BaseVagon&& other) noexcept
{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

BaseVagon::~BaseVagon()
{
	free();
}

unsigned int BaseVagon::getBasePrice() const
{
	return this->basePrice;
}

bool BaseVagon::getIsTaken(size_t row, size_t col) const
{
	return seats[row][col];
}

void BaseVagon::setIsTaken(size_t row, size_t col, bool state)
{
	this->seats[row][col] = state;
}

void BaseVagon::writeVagonBinary(std::ofstream& ofs) const
{
	ofs.write((const char*)&this->seatRows, sizeof(size_t));
	ofs.write((const char*)&this->seatCols, sizeof(size_t));

	

	for (size_t i = 0;i < seatRows;i++) {
		for (size_t j = 0;j < seatCols;j++) {
			ofs.write((const char*)&seats[i][j], sizeof(bool));
		}
	}

	ofs.write((const char*)&ID, sizeof(unsigned int));
	ofs.write((const char*)&basePrice, sizeof(unsigned int));

}

void BaseVagon::readVagonBinary(std::ifstream& ifs)
{
	ifs.read((char*)&seatRows, sizeof(size_t));
	ifs.read((char*)&seatCols, sizeof(size_t));

	if (seats) {
		for (size_t r = 0; r < seatRows; ++r) {
			delete[] seats[r];
		}
		delete[] seats;
		seats = nullptr;
	}
		
	seats = new bool* [seatRows];
	for (size_t i = 0; i < seatRows; ++i) {
		seats[i] = new bool[seatCols];
	}

	for (size_t i = 0;i < seatRows;i++) {
		for (size_t j = 0;j < seatCols;j++) {
			ifs.read((char*)&seats[i][j], sizeof(bool));
		}
	}

	ifs.read((char*)&ID, sizeof(unsigned int));
	ifs.read((char*)&basePrice, sizeof(unsigned int));
}

unsigned int BaseVagon::getWagonID() const
{
	return this->ID;
}

bool**& BaseVagon::getSeats()
{
	return seats;
}

const bool* const* BaseVagon::getSeats() const
{
	return seats;
}

void BaseVagon::setBasePrice(unsigned int price)
{
	this->basePrice = price;
}

void BaseVagon::setWagonID(unsigned int wagonID)
{
	this->ID = wagonID;
}

void BaseVagon::setNextID(unsigned int lastWagonID)
{
	//this->nextID = lastWagonID;
}

