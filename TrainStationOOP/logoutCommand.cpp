#include "logoutCommand.h"

void logoutCommand::execute() const
{
	if (!manager->getUser()) throw std::logic_error("You need to be a logged in to log out!");

	User* normalUser = nullptr;
	manager->setUser(normalUser);
	std::cout << "Successfully logged out!" << std::endl;
}
