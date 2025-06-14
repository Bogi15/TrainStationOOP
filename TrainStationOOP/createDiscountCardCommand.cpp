#include "createDiscountCardCommand.h"
#include "Utility.h"
#include "DiscountCard.h"

void createDiscountCardCommand::execute() const
{
	if (!manager->getUser()) throw std::logic_error("You need to be a logged as admin to use this command!");

	String cardType;
	std::cin >> cardType;
	if (!manager->isValidCardType(cardType)) throw std::invalid_argument("Typed non existant card type");

	DiscountCard* card = Utility::createDiscountCard(cardType);
	card->getInfoForCard();

	std::cout << "Successfully create a discount card in file: ";
	card->printFileName();
	std::cout << std::endl << std::endl;

	card->saveDiscountCardToFile();
	manager->addCardID(card->getDiscountCardID());

}
