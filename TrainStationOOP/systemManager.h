#pragma once
#include "stationsRepository.h"
#include "User.h"

class Station;

class systemManager
{
private:
	stationsRepository data;
	static User* currentUser;

public:
	systemManager();

	void saveAllData() const;
	void loadAllData();

	void addStation(const Station& s);
	void addTrain(const SharedPtr<Train>& t, Station& s);

	void freeTracks();

	const SharedPtr<Train> getTrainByID(unsigned int id) const;
	const Station& getStationByName(const String& name) const;
	Station& getStationByName(const String& name);

	const Vector<Station>& getAllStations()const;
	Vector<Station>& getAllStations();

	const User* getUser() const;

	const Vector<User*>& getAllAdmins() const;
	Vector<User*>& getAllAdmins();

	const Vector<SharedPtr<Train>>& getAllTrains()const;
	Vector<SharedPtr<Train>>& getAllTrains();

	void setUser(User*& user);
	bool containsStation(const String& name);
	bool isValidWagonID(const SharedPtr<Train>& t, unsigned int wagonID);

	void cinFailMessage()const;
	void reserveTrackForTrain(Station& s);
	void printStations()const;

	~systemManager();
	
};

