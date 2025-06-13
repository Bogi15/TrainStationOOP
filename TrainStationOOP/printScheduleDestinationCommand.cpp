#include "printScheduleDestinationCommand.h"

printScheduleDestinationCommand::printScheduleDestinationCommand(systemManager* manager): Command(manager){}

void printScheduleDestinationCommand::execute() const
{
	String stationName, destination;

	std::cin >> stationName;
	Station depart = manager->getStationByName(stationName);

	std::cin >> destination;
	Station arrive = manager->getStationByName(destination);
	
	depart.printTrainsByDestination(destination);
}
