#include "Station.h"
#include "Utility.h"
#include "systemManager.h"


Station::Station(String stationName) : stationName(stationName), numberOfTracks(ConstantsS::NUMBER_OF_TRACKS)
{
	for (size_t i = 0;i < ConstantsS::NUMBER_OF_TRACKS;i++) {
		tracks[i] = false;
	}
}

const String& Station::getStationName() const
{
	return this->stationName;
}

void Station::printSchedule() const
{
	std::cout << "=== Schedule for station " << stationName << " ===" << std::endl << std::endl;

	std::cout << "Arrivals: " << std::endl;
	printArrivaingTrains();
	std::cout << std::endl;
	std::cout << "Departures: " << std::endl;
	printDepartingTrains();
	std::cout << std::endl;


}

void Station::printArrivaingTrains() const
{
	Utility::fillWithDashSign(ConstantsS::MAX_LINE_ARRIVING_TRAIN_LEN);
	std::cout << "| Arrival Time      | Arrival Platform | Train ID | Starting station | Status    |" << std::endl;
	Utility::fillWithDashSign(ConstantsS::MAX_LINE_ARRIVING_TRAIN_LEN);

	for (size_t i = 0;i < arrivingTrains.getSize();i++) {

		SharedPtr<Train> temp = arrivingTrains[i].lock();

		std::cout << "| ";
		std::cout << temp->getArrivalTime() << "  | ";
		std::cout << temp->getArrivalTrack() << "                | ";
		std::cout << temp->getID() << "     | ";
		std::cout << temp->getStartingStation();
		printBlankSpaces(temp->getStartingStation(),ConstantsS::MAX_STARTING_STATION_LEN);
		std::cout<<" | ";
		std::cout << trainStatusArriving(temp->getArrivalTime());
		if (trainStatusArriving(temp->getArrivalTime()) == "To arrive") std::cout << " |";
		else std::cout << "   |";
		std::cout << std::endl;
		
	}
	Utility::fillWithDashSign(ConstantsS::MAX_LINE_ARRIVING_TRAIN_LEN);

}

void Station::printDepartingTrains() const
{
	Utility::fillWithDashSign(ConstantsS::MAX_LINE_DEPARTING_TRAIN_LEN);
	std::cout << "| Departure Time    | Arrival Time     | Destination | Departure Platform | Train ID | Status    |" << std::endl;
	Utility::fillWithDashSign(ConstantsS::MAX_LINE_DEPARTING_TRAIN_LEN);

	for (size_t i = 0;i < departingTrains.getSize();i++) {

		std::cout << "| ";
		std::cout << departingTrains[i]->getDepartureTime() << "  | ";
		std::cout << departingTrains[i]->getArrivalTime() << " | ";
		std::cout << departingTrains[i]->getFinalStation();
		printBlankSpaces(departingTrains[i]->getFinalStation(),ConstantsS::MAX_STATION_NAME_SPACE);
		std::cout << " | ";
		std::cout << departingTrains[i]->getDepartureTrack() << "                  | ";
		std::cout << departingTrains[i]->getID() << "     | ";
		std::cout << trainStatusDeparting(departingTrains[i]->getDepartureTime());
		if (trainStatusDeparting(departingTrains[i]->getDepartureTime()) == "To depart") std::cout << " |";
		else std::cout << "  |";
		std::cout << std::endl;
	}
	Utility::fillWithDashSign(ConstantsS::MAX_LINE_DEPARTING_TRAIN_LEN);

}

void Station::printTrainsByDestination(const String& destination) const
{
	if (!hasDestination(destination)) {
		std::cout << "There is no train going for " << destination << std::endl;
		return;
	}

	std::cout << "=== Schedule for station " << stationName << " ===" << std::endl << std::endl;

	std::cout << "Departures to : " << destination << std::endl;
	Utility::fillWithDashSign(ConstantsS::MAX_LINE_DEPARTING_TRAIN_LEN);
	std::cout << "| Departure Time    | Arrival Time     | Destination | Departure Platform | Train ID | Status    |" << std::endl;
	Utility::fillWithDashSign(ConstantsS::MAX_LINE_DEPARTING_TRAIN_LEN);

	for (size_t i = 0;i<departingTrains.getSize();i++) {
		if (departingTrains[i]->getFinalStation() == destination) {
			std::cout << "| ";
			std::cout << departingTrains[i]->getDepartureTime() << "  | ";
			std::cout << departingTrains[i]->getArrivalTime() << " | ";
			std::cout << departingTrains[i]->getFinalStation();
			printBlankSpaces(departingTrains[i]->getFinalStation(), ConstantsS::MAX_STATION_NAME_SPACE);
			std::cout << " | ";
			std::cout << departingTrains[i]->getDepartureTrack() << "                  | ";
			std::cout << departingTrains[i]->getID() << "     | ";
			std::cout << trainStatusDeparting(departingTrains[i]->getDepartureTime());
			if (trainStatusDeparting(departingTrains[i]->getDepartureTime()) == "To depart") std::cout << " |";
			else std::cout << "  |";
			std::cout << std::endl;
		}
	}

	Utility::fillWithDashSign(ConstantsS::MAX_LINE_DEPARTING_TRAIN_LEN);
}

void Station::printTrainsByTime(const String& date, const String& time) const
{
	String correctFormatTime("");
	correctFormatTime += date;
	correctFormatTime += " ";
	correctFormatTime += time;

	std::cout << "=== Schedule for station " << stationName << " ===" << std::endl << std::endl;

	std::cout << "Departures after : " << correctFormatTime << std::endl;
	Utility::fillWithDashSign(ConstantsS::MAX_LINE_DEPARTING_TRAIN_LEN);
	std::cout << "| Departure Time    | Arrival Time     | Destination | Departure Platform | Train ID | Status    |" << std::endl;
	Utility::fillWithDashSign(ConstantsS::MAX_LINE_DEPARTING_TRAIN_LEN);

	for (size_t i = 0;i < departingTrains.getSize();i++) {
		if (timeInPast(correctFormatTime,departingTrains[i]->getDepartureTime())) {
			std::cout << "| ";
			std::cout << departingTrains[i]->getDepartureTime() << "  | ";
			std::cout << departingTrains[i]->getArrivalTime() << " | ";
			std::cout << departingTrains[i]->getFinalStation();
			printBlankSpaces(departingTrains[i]->getFinalStation(), ConstantsS::MAX_STATION_NAME_SPACE);
			std::cout << " | ";
			std::cout << departingTrains[i]->getDepartureTrack() << "                  | ";
			std::cout << departingTrains[i]->getID() << "     | ";
			std::cout << trainStatusDeparting(departingTrains[i]->getDepartureTime());
			if (trainStatusDeparting(departingTrains[i]->getDepartureTime()) == "To depart") std::cout << " |";
			else std::cout << "  |";
			std::cout << std::endl;
		}
	}

	Utility::fillWithDashSign(ConstantsS::MAX_LINE_DEPARTING_TRAIN_LEN);
	
}


void Station::addDepartingTrain(const SharedPtr<Train>& train)
{
	if (!train) {
		std::cout << "Error: Attempting to add a null train to departingTrains" << std::endl;
		return;
	}

	departingTrains.push_back(train);
}

void Station::addArrivingTrain(const SharedPtr<Train>& train)
{
	if (!train) {
		std::cout << "Error: Attempting to add a null train to arrivingTrains" << std::endl;
		return;
	}

	arrivingTrains.push_back(WeakPtr<Train>(train));
}

const bool* Station::getTracks() const
{
	return tracks;
}

bool* Station::getTracks()
{
	return tracks;
}

size_t Station::getNumberOfTracks() const
{
	return ConstantsS::NUMBER_OF_TRACKS;
}

Vector<SharedPtr<Train>>& Station::getDepartingTrains()
{
	return departingTrains;
}

Vector<WeakPtr<Train>>& Station::getArrivingTrains()
{
	return arrivingTrains;
}

bool Station::reserveTrack(size_t& outTrack)
{
	for (size_t i = 0; i < ConstantsS::NUMBER_OF_TRACKS; ++i) {
		if (!tracks[i]) {
			tracks[i] = true;
			outTrack = i;
			return true;
		}
	}
	return false;
}

void Station::releaseTrack(size_t trackIndex)
{
	if (trackIndex < ConstantsS::NUMBER_OF_TRACKS) {
		tracks[trackIndex] = false;
	}
}

void Station::printTrackStatus() const
{
	std::cout << "Station " << stationName << " track status:" << std::endl;

	std::cout << "Arriving tracks:" << std::endl;
	for (size_t i = 0; i < ConstantsS::NUMBER_OF_TRACKS; i++) {
		std::cout << "  Track " << i + 1 << ": " << (tracks[i] ? "OCCUPIED" : "FREE") << "\n";
	}

}

void Station::writeStationBinary(std::ofstream& ofs) const
{
	stationName.writeBinary(ofs);
	ofs.write((const char*)&numberOfTracks, sizeof(numberOfTracks));
	ofs.write((const char*)&tracks, numberOfTracks * sizeof(bool));

	size_t dTrains = departingTrains.getSize();
	ofs.write((const char*)&dTrains, sizeof(size_t));

	for (size_t i = 0;i < dTrains;i++) {
		unsigned int trainID = departingTrains[i]->getID();
		ofs.write((const char*)&trainID, sizeof(unsigned int));
	}

	size_t aTrains = arrivingTrains.getSize();
	ofs.write((const char*)&aTrains, sizeof(size_t));

	for (size_t i = 0;i < aTrains;i++) {
		SharedPtr<Train> t =  arrivingTrains[i].lock();
		unsigned int trainID = t->getID();
		ofs.write((const char*)&trainID, sizeof(unsigned int));
	}

}

void Station::readStationBinary(std::ifstream& ifs)
{
	systemManager manager;

	stationName.readBinary(ifs);
	ifs.read((char*)&numberOfTracks, sizeof(numberOfTracks));
	ifs.read((char*)&tracks, numberOfTracks * sizeof(bool));

	size_t dTrains;
	ifs.read((char*)&dTrains, sizeof(size_t));
	departingTrains.clear();
	for (size_t i = 0;i < dTrains;i++) {
		unsigned int trainID;
		ifs.read((char*)&trainID, sizeof(unsigned int));
		SharedPtr<Train> t = manager.getTrainByID(trainID);
		if (t.get() != nullptr) departingTrains.push_back(t);
	}

	size_t aTrains;
	ifs.read((char*)&aTrains, sizeof(size_t));
	arrivingTrains.clear();
	for (size_t i = 0;i < aTrains;i++) {
		unsigned int trainID;
		ifs.read((char*)&trainID, sizeof(unsigned int));
		SharedPtr<Train> t = manager.getTrainByID(trainID);
		if (t.get() != nullptr) arrivingTrains.push_back(WeakPtr<Train>(t));
	}
	
}

String Station::trainStatusArriving(const String& arrivingTime) const
{
	std::tm target = Utility::parseDateTime(arrivingTime);
	std::time_t target_t = Utility::toTimeT(target);

	std::time_t now_t = std::time(0);

	if (now_t >= target_t) {
		return String("Arrived");
	}
	else {
		return String("To arrive");
	}
}

String Station::trainStatusDeparting(const String& departingTime) const
{
	std::tm target = Utility::parseDateTime(departingTime);
	std::time_t target_t = Utility::toTimeT(target);

	std::time_t now_t = std::time(0);

	if (now_t >= target_t) {
		return String("Departed");
	}
	else {
		return String("To depart");
	}
}

bool Station::timeInPast(const String& dateTime, const String& departingTime) const
{
	std::tm targetTm = Utility::parseDateTime(dateTime);
	std::time_t target_t = Utility::toTimeT(targetTm);

	std::tm departingTm = Utility::parseDateTime(departingTime);
	std::time_t departing_t = Utility::toTimeT(departingTm);

	return departing_t >= target_t;
}

bool Station::hasDestination(const String& destination) const
{
	bool hasDes = false;
	for (size_t i = 0;i < departingTrains.getSize();i++) {
		if (departingTrains[i]->getFinalStation() == destination) {
			hasDes = true;
			break;
		}
	}

	return hasDes;
}

void Station::printBlankSpaces(const String& stationName, size_t maxLen) const
{
	size_t len = maxLen - stationName.getSize();

	while (len--) {
		std::cout << " ";
	}
}
