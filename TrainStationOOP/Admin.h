#pragma once
#include "User.h"
#include "String.h"

class Admin : public User
{
protected:
	String name;
	String password;

public:

	void addTrain(const String& startingStation, const String& finalStation, unsigned int distance, unsigned int speed, const String& departureTime);
	//add-train <station> <destination> <distance> <speed> <departureDate> departureTime> 
	//remove-train <trainID>
	//add-wagon <trainID> <wagonType> <basePrice> [extra params] 
	//remove-wagon <trainID> <wagonID>
	//move-wagon 
};

