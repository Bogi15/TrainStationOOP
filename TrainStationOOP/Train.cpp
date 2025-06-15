#include "Train.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include "Utility.h"

unsigned int Train::nextID = 1000;

double Train::getTimeNeededForTheTrainToArrive() const
{
	return (double)this->distance / this->speed;
}

String Train::calculateArrivalTime(const String& departureTime) const
{
	std::time_t dep_t = convertStringToTime(departureTime);
	double hoursNeeded = getTimeNeededForTheTrainToArrive();
	std::time_t travelSec = static_cast<std::time_t>(std::llround(hoursNeeded * 3600.0));

	std::time_t arr_t = dep_t + travelSec;

	std::tm* ptm = std::localtime(&arr_t);
	if (!ptm) {
		throw std::runtime_error("localtime failed on arrival timestamp");
	}

	char buf[20];
	if (std::strftime(buf, sizeof(buf), "%d/%m/%Y %H:%M", ptm) == 0) {
		throw std::runtime_error("strftime failed");
	}

	return String(buf);
}

time_t Train::convertStringToTime(const String& departureTime) const
{
	std::tm tm{}; 
	std::istringstream ss(departureTime.c_str());
	ss >> std::get_time(&tm, "%d/%m/%Y %H:%M");
	if (ss.fail()) {
		throw std::runtime_error("Failed to parse time string: " + std::string(departureTime.c_str()));
	}
	tm.tm_sec = 0;   
	tm.tm_isdst = -1;   
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
	this->ID = other.ID + 1;
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

Train::Train(const String& startingStarion, const String& finalStation, unsigned int distance, unsigned int speed, const String& departureTime, size_t departureTrack, size_t arrivalTrack)
	: startingStation(startingStarion), finalStation(finalStation), distance(distance), speed(speed), departureTime(departureTime), departureTrack(departureTrack),arrivalTrack(arrivalTrack)
{
	this->ID = nextID++;
	this->arrivalTime = calculateArrivalTime(departureTime);
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

Train::~Train()
{
	free();
}

const String& Train::getStartingStation() const{ return startingStation;}

const String& Train::getFinalStation() const
{
	return finalStation;
}

const String& Train::getDepartureTime() const
{
	return departureTime;
}

const String& Train::getArrivalTime() const
{
	return arrivalTime;
}

size_t Train::getDepartureTrack() const
{
	return departureTrack;
}

size_t Train::getArrivalTrack() const
{
	return arrivalTrack;
}

unsigned int Train::getDistance() const
{
	return distance;
}

unsigned int Train::getID() const
{
	return ID;
}

unsigned int Train::getSpeed() const
{
	return speed;
}

const Vector<BaseVagon*>& Train::getVagons() const
{
	return vagons;
}

Vector<BaseVagon*>& Train::getVagons()
{
	return vagons;
}

unsigned int Train::getNextID()
{
	return nextID;
}

void Train::setStartingStation(const String& station)
{
	startingStation = station;
}

void Train::setFinalStation(const String& station)
{
	finalStation = station;
}

void Train::setDepartureTime(const String& time)
{
	departureTime = time;
}

void Train::setArrivalTime(const String& time)
{
	arrivalTime = time;
}

void Train::setDepartureTrack(size_t track)
{
	departureTrack = track;
}

void Train::setArrivalTrack(size_t track)
{
	arrivalTrack = track;
}

void Train::setDistance(unsigned int dist)
{
	distance = dist;
}

void Train::setID(unsigned int id)
{
	ID = id;
}

void Train::setNextID(unsigned int id)
{
	nextID = id;
}

void Train::setSpeed(unsigned int spd)
{
	speed = spd;
}

void Train::setVagons(const Vector<BaseVagon*>& vs)
{
	vagons = vs;
}

void Train::addVagon(BaseVagon*& vagon)
{
	unsigned int id = ++nextVagonID;
	vagon->setWagonID(id);
	vagons.push_back(vagon);

}

void Train::removeVagon(unsigned int vagonID)
{
	if (vagonID <= vagons.getSize() + 1) {
		vagons.remove(vagonID - 1);
		std::cout << "Successfully removed wagon with ID " << vagonID <<std::endl;
	}

	std::cout << "The provided wagon ID is not valid" << std::endl;
}

void Train::printTrain() const
{
	std::cout << "===Train ID:" << ID << "===" << std::endl;
	std::cout << "Starting Station: " << startingStation << std::endl;
	std::cout << "Destination: " << finalStation << std::endl;
	std::cout << "Distance: " << distance << " km" << std::endl;
	std::cout << "Speed: " << speed << "km/h" << std::endl;
	std::cout << "Departure Time: " << departureTime << std::endl;
	std::cout << "Arrival Time: " << arrivalTime << std::endl;
	std::cout << "Departure Platform: " << departureTrack + 1 << std::endl;
	std::cout << std::endl;
	std::cout << "Wagons:" << std::endl;
	for (size_t i = 0;i < vagons.getSize();i++) {
		std::cout << i + 1 << " - " << vagons[i]->getTypeWagonString() << std::endl;
	}
	std::cout << std::endl;
}

void Train::printWagon() const
{
	
}

void Train::printVagons() const
{
	for (size_t i = 0;i < vagons.getSize();i++) {
		std::cout << "Vagon ID: " << vagons[i]->getWagonID() << std::endl;
		vagons[i]->printUnoccupiedSeats();
	}

	std::cout << std::endl;
}

void Train::getSeat(unsigned int vagonID, size_t seat)
{
	getVagonByID(vagonID)->buyPlaceOnSeat(seat);
}

const BaseVagon* Train::getVagonByID(unsigned int vagonID) const
{
	return vagons[vagonID - 1];
}

BaseVagon*& Train::getVagonByID(unsigned int vagonID)
{
	if (vagonID > nextVagonID || vagonID <= 0) {
		throw std::invalid_argument("Wagon with such ID does not exist!");
	}

	return vagons[vagonID - 1];
}

BaseVagon* Train::detachWagon(unsigned int wagonID)
{
	for (size_t i = 0;i < vagons.getSize();i++) {
		if (vagons[i]->getWagonID() == wagonID) {
			BaseVagon* ptr = vagons[i];
			vagons.remove(i);
			return ptr;
		}
	}

	return nullptr;
}

void Train::writeTrainBinary(std::ofstream& ofs) const
{
	startingStation.writeBinary(ofs);
	finalStation.writeBinary(ofs);
	departureTime.writeBinary(ofs);
	arrivalTime.writeBinary(ofs);
	ofs.write((const char*)&departureTrack, sizeof(size_t));
	ofs.write((const char*)&arrivalTrack, sizeof(size_t));	
	ofs.write((const char*)&distance, sizeof(unsigned int));
	ofs.write((const char*)&ID, sizeof(unsigned int));
	ofs.write((const char*)&speed, sizeof(unsigned int));
	ofs.write((const char*)&nextVagonID, sizeof(unsigned int));

	size_t count = vagons.getSize();
	ofs.write((const char*)&count, sizeof(size_t));

	for (size_t i = 0;i < vagons.getSize();i++) {
		VagonType tag = vagons[i]->typeVagon();
		ofs.write((const char*)&tag, sizeof(VagonType));

		vagons[i]->writeVagonBinary(ofs);
	}
}

void Train::readTrainBinary(std::ifstream& ifs)
{
	startingStation.readBinary(ifs);
	finalStation.readBinary(ifs);
	departureTime.readBinary(ifs);
	arrivalTime.readBinary(ifs);
	ifs.read((char*)&departureTrack, sizeof(size_t));
	ifs.read((char*)&arrivalTrack, sizeof(size_t));
	ifs.read((char*)&distance, sizeof(unsigned int));
	ifs.read((char*)&ID, sizeof(unsigned int));
	ifs.read((char*)&speed, sizeof(unsigned int));
	ifs.read((char*)&nextVagonID, sizeof(unsigned int));

	size_t count = 0;;
	ifs.read((char*)&count, sizeof(count));
	vagons.clear();
	
	for (size_t i = 0;i < count;i++) {
		BaseVagon* v = Utility::readFromStream(ifs);
		vagons.push_back(v);
	}
}
