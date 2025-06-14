#include "addWagonCommand.h"
#include "Utility.h"

void addWagonCommand::execute() const
{
	if (!manager->getUser()) throw std::logic_error("You need to be a logged as admin to use this command!");

	unsigned int trainID;
	std::cin >> trainID;
	manager->cinFailMessage();

	SharedPtr<Train> t = manager->getTrainByID(trainID);
	if (!t)throw std::invalid_argument("Train with such ID does not exist!");

	String wagonType;
	std::cin >> wagonType;

	BaseVagon* wagon = Utility::createWithString(wagonType);
	if (!wagon) throw std::invalid_argument("The given type is incorrect");

	t->addVagon(wagon);
	
	std::cout << std::endl << wagon->getTypeWagonString() << "wagon with ID " << wagon->getWagonID() << " added to train " << t->getID() << std::endl;
}
