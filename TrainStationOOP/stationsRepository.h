#pragma once
#include "Station.h"

namespace namesOfFiles {
	constexpr const char* allAdminsFile = "admins.bin";
	constexpr const char* allStationsFile = "stations.bin";
	constexpr const char* allTrainsFile = "trains.bin";
	constexpr const char* allIDcardsFile = "cardsID.bin";


}

class User;

class stationsRepository
{
private:
	static Vector<Station> allStations;
	static Vector<SharedPtr<Train>> allTrains;
	Vector<User*> admins;
	Vector<unsigned int> discountCardIDs;

public:

	const Vector<Station>& getAllStations()const;
	Vector<Station>& getAllStations();

	const Vector<SharedPtr<Train>>& getAllTrains() const;
	Vector<SharedPtr<Train>>& getAllTrains();

	SharedPtr<Train> getTrainByID(unsigned int id) const;
	Vector<User*>& getAllAdmins();
	const Vector<User*>& getAllAdmins()const;

	const Vector<unsigned int> getAllDiscountCardIDs()const;

	const Station& getStationByName(const String& name) const;
	Station& getStationByName(const String& name);

	void addTrain(const SharedPtr<Train>& t);
	void addStation(const Station& s);
	void addCardID(unsigned int id);

	bool removeTrain(SharedPtr<Train> t);

	void saveAllStationsInFile()const;
	void loadAllStationsFromFile();

	void saveAllTrainsInFile()const;
	void loadAllTrainsFromFile();

	void saveAllAdminsInFile()const;
	void loadAllAdminsFromFile();

	void saveAllCardsIDs()const;
	void loadAllCardsIDs();

	void clearAllStaions();
	void clearAllTrains();
};

