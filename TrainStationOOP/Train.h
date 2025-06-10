#pragma once
#include "String.h"
#include "Vector.hpp"
#include "BaseVagon.h"

class Train
{
private:

	double getTimeNeededForTheTrainToArrive() const;
	String calculateArrivalTime(const String& departureTime) const;
	time_t convertStringToTime(const String& departureTime) const;


	void free();
	void copyFrom(const Train& other);
	void moveFrom(Train&& other) noexcept;

protected:
	String startingStation = "";
	String finalStation = "";
	String departureTime = "";
	String arrivalTime = "";
	size_t departureTrack;
	size_t arrivalTrack;
	unsigned int distance;
	unsigned int ID;
	unsigned int speed;
	Vector <BaseVagon*> vagons;

	static unsigned int nextID;


public:

	Train() = default;
	Train(const String& startingStarion, const String& finalStation, unsigned int distance, unsigned int speed, const String& departureTime);
	Train(const Train& other);
	Train(Train&& other) noexcept;
	Train& operator=(const Train& other);
	Train& operator=(Train&& other) noexcept;

	void printVagons() const;

};

