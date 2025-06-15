#include "removeTrainCommand.h"

void removeTrainCommand::execute() const
{
	if (!manager->getUser()) throw std::logic_error("You need to be a logged as admin to use this command!");

	unsigned int trainID;
	std::cin >> trainID;
	manager->cinFailMessage();

	SharedPtr<Train> t = manager->getTrainByID(trainID);
	if (!t) throw std::invalid_argument("Train with such ID does not exist!");

	if (!manager->removeTrain(t)) throw std::runtime_error("Failed to remove train from system.");

	Station& departS = manager->getStationByName(t->getStartingStation());
	departS.releaseTrack(t->getDepartureTrack());

	Station& arriveS = manager->getStationByName(t->getFinalStation());
	arriveS.releaseTrack(t->getArrivalTrack());

	for (size_t i = 0;i < manager->getAllStations().getSize();i++) {
		manager->getAllStations()[i].removeArrivingTrain(trainID);
		manager->getAllStations()[i].removeDepartingTrain(trainID);
	}

	std::cout << "Train " << trainID << " removed successfully! \n" << std::endl;

}
