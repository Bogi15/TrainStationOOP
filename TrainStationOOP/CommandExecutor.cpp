#include "CommandExecutor.h"

CommandExecutor::CommandExecutor(systemManager* m) : manager(m){}

void CommandExecutor::executeCommand()
{	
	manager->loadAllData();
	String c_command;
	while (true) {
		std::cout << ">";
		std::cin >> c_command;

		if (c_command == "exit") {
			manager->saveAllData();
			std::cout << "The system is shutting down" << std::endl;
			std::cout << "Bye....." << std::endl;
			break;
		}

		try {

			Command* command = createCommand(c_command, manager);
			command->execute();
			delete command;
		}
		catch (std::exception& e) {
			std::cout << e.what() << std::endl;
			char buffer[1024];
			std::cin.getline(buffer, 1024);	
		}
	}
}
