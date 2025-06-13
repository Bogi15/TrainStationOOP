#include "addStationCommand.h"

void addStationCommand::execute() const
{
	if (!manager->getUser()) throw std::logic_error("You need to be a logged as admin to use this command!");

	String stationName;
	std::cin >> stationName;
	
	if (manager->containsStation(stationName)) throw std::logic_error("The station already exists!");

	manager->addStation(stationName);
	std::cout << "Added station " << stationName << "!" << std::endl << std::endl;
}
