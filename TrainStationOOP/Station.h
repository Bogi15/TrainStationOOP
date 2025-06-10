#pragma once
#include "Vector.hpp"
#include "Train.h"


class Station
{
protected:
	String stationName;
	bool* tracks;
	Vector<Train> trains;

public:

	Station(String stationName);

	const String& getStationName()const;

	void printSchedule() const;



};

