#include "printSchedule.h"

printSchedule::printSchedule(systemManager* manager):Command(manager){}

void printSchedule::execute() const
{
	String stationName;
	std::cin >> stationName;

	Station s = manager->getStationByName(stationName);

	s.printSchedule();

}
