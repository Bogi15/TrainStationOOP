#include "User.h"

void User::printStations(const Vector<Station>& stations) const
{
	if (stations.getSize() == 0) {
		std::cout << "No stations!" << std::endl;
		return;
	}

	std::cout << "Stations:" << std::endl;

	for (size_t i = 0;i < stations.getSize();i++) {
		std::cout << i + 1 << ". " << stations[i].getStationName() << std::endl;
	}

	std::cout << std::endl;
}

void User::printSchedule(const Station& station) const
{
	station.printSchedule();
}

void User::printScheduleToDestination(const Station& station, const String& destination) const
{
	station.printTrainsByDestination(destination);
}

void User::printScheduleAfterTime(const Station& station, const String& date, const String& time) const
{
	station.printTrainsByTime(date, time);
}

void User::printTrainInfo(const Train& train) const
{
	train.printTrain();
}

void User::printWagonInfo(const Train& train, int wagonID) const
{
	train.getVagonByID(wagonID)->printWagon();
}

void User::buyTicket(Train& train, unsigned int vagonID, size_t seat, const String& ticketFileName, const Vector<String>& extraParams) const
{

}

bool User::isAdmin() const
{
	return false;
}

