#include "BaseVagon.h"
#include <iostream>
#include <iomanip>
#include <utility>

unsigned int BaseVagon::nextID = 1;

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
	this->ID = BaseVagon::ID++;
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

void BaseVagon::moveFrom(BaseVagon&& other)
{
	this->seatRows = other.seatRows;
	this->seatCols = other.seatCols;
	this->ID = other.ID;
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
	this->ID = nextID++;

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

BaseVagon::BaseVagon(BaseVagon&& other)
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

BaseVagon& BaseVagon::operator=(BaseVagon&& other)
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

unsigned int BaseVagon::getVagonID() const
{
	return this->ID;
}

