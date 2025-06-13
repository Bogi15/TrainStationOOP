#pragma once
#include "String.h"
#include "Vector.hpp"
#include "BaseVagon.h"


class Station;

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
	size_t departureTrack = 0;;
	size_t arrivalTrack = 0;
	unsigned int distance = 0;
	unsigned int ID = 0;
	unsigned int speed = 0;
	Vector <BaseVagon*> vagons = {};

	static unsigned int nextID;

public:

	Train() = default;
	Train(const String& startingStarion, const String& finalStation, unsigned int distance, unsigned int speed, const String& departureTime, size_t departureTrack, size_t arrivalTrack);
	Train(const Train& other);
	Train(Train&& other) noexcept;
	Train& operator=(const Train& other);
	Train& operator=(Train&& other) noexcept;
	~Train();

	const String& getStartingStation() const;
	const String& getFinalStation() const;
	const String& getDepartureTime() const;
	const String& getArrivalTime() const;
	size_t getDepartureTrack() const;
	size_t getArrivalTrack() const;
	unsigned int getDistance() const;
	unsigned int getID() const;
	unsigned int getSpeed() const;
	const Vector<BaseVagon*>& getVagons() const;
	static unsigned int getNextID();

	void setStartingStation(const String& station);
	void setFinalStation(const String& station);
	void setDepartureTime(const String& time);
	void setArrivalTime(const String& time);
	void setDepartureTrack(size_t track);
	void setArrivalTrack(size_t track);
	void setDistance(unsigned int dist);
	void setID(unsigned int id);
	static void setNextID(unsigned int id);
	void setSpeed(unsigned int spd);
	void setVagons(const Vector<BaseVagon*>& vs);

	void addVagon(const BaseVagon& vagon);
	void removeVagon(unsigned int vagonID);

	void printTrain()const;
	void printWagon()const;
	void printVagons() const;
	
	void getSeat(unsigned int vagonID, size_t seat);
	const BaseVagon* getVagonByID(unsigned int vagonID)const;
	BaseVagon*& getVagonByID(unsigned int vagonID);

	void writeTrainBinary(std::ofstream& ofs) const;
	void readTrainBinary(std::ifstream& ifs);


};

