#include "addTrainCommand.h"
#include "Utility.h"
#include "TrackAllocator.h"

void addTrainCommand::execute() const
{


	if (!manager->getUser()) throw std::logic_error("You need to be a logged as admin to use this command!");

	String departS, arriveS;

	std::cin >> departS;
	if(!manager->containsStation(departS)) throw std::logic_error("Error: No such station!");

	std::cin >> arriveS;
	if (!manager->containsStation(departS)) throw std::logic_error("Error: No such station!");

	unsigned int distance, speed;

	std::cin >> distance;
	manager->cinFailMessage();

	std::cin >> speed;
	manager->cinFailMessage();

	String date, time;

	std::cin >> date;
	if (!Utility::isValidDate(date)) throw std::invalid_argument("Wrong format date");

	std::cin >> time;
	if(!Utility::isValidHour(time)) throw std::invalid_argument("Wrong format hour");

	size_t departingTrack = 0, arrivingTrack = 0;

	Station& departStation = manager->getStationByName(departS);
	Station& arriveStation = manager->getStationByName(arriveS);

	if (!TrackAllocator::allocateTracks(departStation, arriveStation, departingTrack, arrivingTrack)) throw std::logic_error("Could not reserve tracks!");

	SharedPtr<Train> trainPtr(new Train(departS, arriveS, distance, speed, date + " " + time, departingTrack, arrivingTrack));
 
	manager->getAllTrains().push_back(trainPtr);

	departStation.getDepartingTrains().push_back(trainPtr);

	WeakPtr<Train> wptr(trainPtr);
	arriveStation.getArrivingTrains().push_back(wptr);


	std::cout << "Train successfully added with ID: " << trainPtr->getID() << std::endl;
}
