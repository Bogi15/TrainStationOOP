#include "validateDiscountCardCommand.h"

void validateDiscountCardCommand::execute() const
{
	if (!manager->getUser()) throw std::logic_error("You need to be a logged as admin to use this command!");

	unsigned int possibleID;
	std::cin >> possibleID;
	manager->cinFailMessage();

	if (!manager->isValidCardID(possibleID)) throw std::logic_error("The provided ID is not in the list!");
	else std::cout << "The ID is valid!" << std::endl;
}
