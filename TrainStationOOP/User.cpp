#include "User.h"

void User::printStations() const
{
	std::cout << "The program has these stations in the database: " << std::endl;
	for (size_t i = 0;i < this->stations.getSize();i++) {
		std::cout << this->stations[i].getStationName() << std::endl;
	}
}

void User::priintSchedule(String station) const
{
	int index = -1;

	for (size_t i = 0;i < this->stations.getSize();i++) {
		if (this->stations[i].getStationName() == station) {
			index = i;
			break;
		}
	}

	if (index == -1) {
		std::cout << "Error: No such station!" << std::endl;
		return;
	}

	std::cout << std::endl << "=== Schedule for station " << this->stations[index].getStationName() << " ===" << std::endl;


}
