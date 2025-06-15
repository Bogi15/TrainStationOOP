#include "moveWagonCommand.h"
#include "Utility.h"

void moveWagonCommand::execute() const
{
	unsigned int sourceTrainID;
	manager->cinFailMessage();
	std::cin >> sourceTrainID;

	SharedPtr<Train> sourceT = manager->getTrainByID(sourceTrainID);
	if (!sourceT)throw std::invalid_argument("Train with such ID does not exist!");

	if (Utility::hasDeparted(sourceT->getDepartureTime())) throw std::logic_error("The first train has already departed!");

	unsigned int wagonID;
	std::cin >> wagonID;
	manager->cinFailMessage();

	unsigned int destinationTrainID;
	std::cin >> destinationTrainID;
	manager->cinFailMessage();

	SharedPtr<Train> destinationT = manager->getTrainByID(destinationTrainID);
	if (!destinationT)throw std::invalid_argument("Train with such ID does not exist!");

	if (Utility::hasDeparted(destinationT->getDepartureTime())) throw std::logic_error("The second train has already departed!");

	BaseVagon* wagon = sourceT->detachWagon(wagonID);
	if (!wagon) throw std::invalid_argument("Wagon with such ID does not exist!");

	if (!wagon->wagonIsFree()) throw std::logic_error("Can't move wagon with bought seats!");

	destinationT->addVagon(wagon);
}
