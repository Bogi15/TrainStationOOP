#pragma once
#include "Shared_Weak_ptr.hpp"
#include "Train.h"


namespace ConstantsS {
	//constexpr int NUMBER_OF_SYMBOLS_ARRIVAL = 
	constexpr int NUMBER_OF_TRACKS = 8;
	constexpr int MAX_LINE_ARRIVING_TRAIN_LEN = 82;
	constexpr int MAX_LINE_DEPARTING_TRAIN_LEN = 98;
	constexpr int MAX_STATION_NAME_SPACE = 11;
	constexpr int MAX_STARTING_STATION_LEN = 16;

}

class systemManager;

class Station
{
private:
	String stationName;
	bool tracks[ConstantsS::NUMBER_OF_TRACKS];	
	unsigned int numberOfTracks;
	Vector<SharedPtr<Train>> departingTrains;
	Vector<WeakPtr<Train>> arrivingTrains;

	String trainStatusArriving(const String& arrivingTime)const;
	String trainStatusDeparting(const String& departingTime)const;
	bool timeInPast(const String& dateTime, const String& departingTime)const;

	bool hasDestination(const String& destination)const;
	void printBlankSpaces(const String& stationName, size_t maxLen)const;

public:

	Station() = default;
	Station(String stationName);

	const String& getStationName()const;

	void printSchedule() const;
	void printArrivaingTrains()const;
	void printDepartingTrains()const;
	void printTrainsByDestination(const String& destination)const;
	void printTrainsByTime(const String& date, const String& time)const;

	void addDepartingTrain(const SharedPtr<Train>& train);
	void addArrivingTrain(const SharedPtr<Train>& train);

	const bool* getTracks()const;
	bool* getTracks();
	size_t getNumberOfTracks()const;

	Vector<SharedPtr<Train>>& getDepartingTrains();
	Vector<WeakPtr<Train>>& getArrivingTrains();

	bool reserveTrack(size_t& outTrack);
	void releaseTrack(size_t trackIndex);
	void printTrackStatus()const;

	void writeStationBinary(std::ofstream& ofs) const;
	void readStationBinary(std::ifstream& ifs);
};

