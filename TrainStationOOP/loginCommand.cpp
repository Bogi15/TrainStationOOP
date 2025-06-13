#include "loginCommand.h"
#include "Admin.h"


void loginCommand::execute() const
{
	if (manager->getUser()) throw std::logic_error("You are already logged in!");

	String name, password;
	std::cin >> name;
	std::cin >> password;

	for (size_t i = 0;i < manager->getAllAdmins().getSize();i++) {
		Admin* a = dynamic_cast<Admin*>(manager->getAllAdmins()[i]);
		if (name == a->getName() && a->validatePassword(password)) {
			manager->setUser(manager->getAllAdmins()[i]);
			std::cout << "Welcome back, "<< name << "!" << std::endl << std::endl;

			for (size_t i = 0;i < manager->getAllStations().getSize();i++) {
				manager->getAllStations()[i].printSchedule();
			}

			return;
		}

	}

	throw std::runtime_error("No such admin with these credentials");

}
