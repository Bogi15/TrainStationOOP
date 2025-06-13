#include "printStationsCommand.h"

printStationsCommand::printStationsCommand(systemManager* manager): Command(manager){}

void printStationsCommand::execute() const
{
	manager->printStations();
}
