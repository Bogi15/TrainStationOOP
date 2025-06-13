#include "printTrainWagonCommand.h"

void printTrainWagonCommand::execute() const
{
	unsigned int trainID, wagonID;
	
	std::cin >> trainID;
	manager->cinFailMessage();
	SharedPtr<Train> t = manager->getTrainByID(trainID);
	if (!t) throw std::invalid_argument("Train with such ID does not exist!");

	std::cin >> wagonID;
	manager->cinFailMessage();
	if (!manager->isValidWagonID(t, wagonID)) throw std::invalid_argument("The wagon ID is not correct!");

	t->getVagonByID(wagonID)->printWagon();
}
