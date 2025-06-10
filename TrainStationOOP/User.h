#pragma once
#include "String.h"
#include "Vector.hpp"
#include "Station.h"



class User
{
private:
	Vector<Station> stations;

	void printArrivals() const;
	void printDepartures() const;

public:

	void printStations() const;
	void priintSchedule(String station) const;
	void printScheduleDestination(String station , String destination) const;
	//void printScheduleTime(Station, Date, Time) const;
	void printTrain(Train ID) const;
	void printWagon(Train ID, unsigned int ZagonID) const;
	//void buyTicketDiscount(Train ID, unsigned int vagonID, unsigned int seatID, String cardFile);
};

