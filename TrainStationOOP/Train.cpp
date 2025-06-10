#include "Train.h"
#include <iomanip>
#include <iostream>
#include <sstream>

unsigned int Train::nextID = 1000;

double Train::getTimeNeededForTheTrainToArrive() const
{
	return (double)this->distance / this->speed;
}

String Train::calculateArrivalTime(const String& departureTime) const
{
	size_t travelHours = (size_t)getTimeNeededForTheTrainToArrive();
	double fractionPart = getTimeNeededForTheTrainToArrive() - travelHours;
	size_t travelMinutes = (size_t)(std::round(fractionPart * 60));

	std::time_t travelSecond = (travelHours * 3600) + (travelMinutes * 60);
	std::time_t arrivalTime = convertStringToTime(departureTime.c_str()) + travelSecond;

	return std::ctime(&arrivalTime);
}

time_t Train::convertStringToTime(const String& departureTime) const
{
		std::tm tm = {};
		std::istringstream ss(departureTime.c_str());
		ss >> std::get_time(&tm, "%d/%m/%Y %H:%M");

		if (ss.fail()) {
			throw std::runtime_error("Failed to parse time string!");
		}

		return std::mktime(&tm);
}

void Train::free()
{
	for (size_t i = 0;i < vagons.getSize();i++) {
		delete vagons[i];
		vagons[i] = nullptr;
	}
	vagons.clear();
}

void Train::copyFrom(const Train& other)
{
	this->startingStation = other.startingStation;
	this->finalStation = other.finalStation;
	this->departureTime = other.departureTime;
	this->arrivalTime = other.arrivalTime;
	this->departureTrack = other.departureTrack;
	this->arrivalTrack = other.arrivalTrack;
	this->distance = other.distance;
	this->ID = other.ID;
	this->speed = other.speed;

	for (size_t i = 0; i < other.vagons.getSize();i++) {

		vagons.push_back(other.vagons[i]->clone());
	}
}

void Train::moveFrom(Train&& other) noexcept
{
	this->startingStation = std::move(other.startingStation);
	this->finalStation = std::move(other.finalStation);
	this->departureTime = std::move(other.departureTime);
	this->arrivalTime = std::move(other.arrivalTime);
	this->departureTrack = other.departureTrack;
	this->arrivalTrack = other.arrivalTrack;
	this->distance = other.distance;
	this->ID = other.ID; // moje bi nextID++ ako mi trqbva razlichjo id
	this->speed = other.speed;

	for (size_t i = 0; i < other.vagons.getSize();i++) {

		this->vagons.push_back(other.vagons[i]);
		other.vagons[i] = nullptr;
	}

	other.vagons.clear();
}

Train::Train(const String& startingStarion, const String& finalStation, unsigned int distance, unsigned int speed, const String& departureTime)
	: startingStation(startingStarion), finalStation(finalStation), distance(distance), speed(speed), departureTime(departureTime)
{
	this->ID = nextID++;
	this->arrivalTime = calculateArrivalTime(departureTime);
	//trqbva za track funckiq

}

Train::Train(const Train& other)
{
	copyFrom(other);
}

Train::Train(Train&& other) noexcept
{
	moveFrom(std::move(other));
}

Train& Train::operator=(const Train& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

Train& Train::operator=(Train&& other) noexcept
{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}	

	return *this;
}

void Train::printVagons() const
{
	for (size_t i = 0;i < vagons.getSize();i++) {
		std::cout << "Vagon ID: " << vagons[i]->getVagonID() << std::endl;
		vagons[i]->printUnoccupiedSeats();
	}

	std::cout << std::endl;
}
