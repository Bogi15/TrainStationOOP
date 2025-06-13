#pragma once
#include "User.h"
#include "String.h"

class Admin : public User
{
protected:
	String name;
	String password;

public:
	bool isAdmin()const override;

	void addTrain(const String& startingStation, const String& finalStation, unsigned int distance, unsigned int speed, const String& departureTime);
	void removeTrain(unsigned int trainID);
	void addWagon(unsigned int trainID, VagonType& wagonType, unsigned int basePrice, Vector <String>& extraParams);
	void removeWagon(unsigned int trainID, unsigned int wagonID);

	void writeBinary(std::ofstream& ofs) const override;
	void readBinary(std::ifstream& ifs) override;

	const String& getName()const;
	bool validatePassword(const String& p)const;
};

