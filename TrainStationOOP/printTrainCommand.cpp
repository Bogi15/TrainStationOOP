#include "printTrainCommand.h"

void printTrainCommand::execute() const
{
	unsigned int ID;

	std::cin >> ID;
	manager->cinFailMessage();

	SharedPtr<Train> t = manager->getTrainByID(ID);
	if (!t) throw std::invalid_argument("Train with such ID does not exist!");
	t->printTrain();
}
