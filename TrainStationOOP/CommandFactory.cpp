#include "CommandFactory.h"

Command* createCommand(const String& command, systemManager* manager) {

	if (command == "print-stations")
		return new printStationsCommand(manager);
	else if (command == "print-schedule")
		return new printSchedule(manager);
	else if (command == "print-schedule-destination")
		return new printScheduleDestinationCommand(manager);
	else if (command == "login")
		return new loginCommand(manager);
	else if (command == "add-station")
		return new addStationCommand(manager);
	else if (command == "add-train")
		return new addTrainCommand(manager);
	else if (command == "print-train")
		return new printTrainCommand(manager);
	else if (command == "print-schedule-time")
		return new printScheduleTimeCommand(manager);
	else if (command == "print-wagon")
		return new printTrainWagonCommand(manager);
	else if (command == "logout")
		return new logoutCommand(manager);
	else if (command == "create-discount-card")
		return new createDiscountCardCommand(manager);
	else if (command == "validate-discount-card")
		return new validateDiscountCardCommand(manager);
	else if (command == "remove-train")
		return new removeTrainCommand(manager);
	else if (command == "add-wagon")
		return new addWagonCommand(manager);
	else if (command == "buy-ticket")
		return new buyTicketCommand(manager);
	else if (command == "buy-ticket-discount")
		return new buyTicketDIscountCommand(manager);
	else if (command == "move-wagon")
		return new moveWagonCommand(manager);
	throw std::exception("Non existing command!");
}