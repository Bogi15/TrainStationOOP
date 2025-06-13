#include "printScheduleTimeCommand.h"
#include "Utility.h"

void printScheduleTimeCommand::execute() const
{
	String stationName;

	std::cin >> stationName;
	Station s = manager->getStationByName(stationName);

	String date, time;

	std::cin >> date;
	if (!Utility::isValidDate(date)) throw std::invalid_argument("Wrong format date!");

	std::cin >> time;
	if (!Utility::isValidHour(time)) throw std::invalid_argument("Wrong format hour!");

	s.printTrainsByTime(date, time);
}
