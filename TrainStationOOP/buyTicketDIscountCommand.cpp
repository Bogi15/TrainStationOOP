#include "buyTicketDIscountCommand.h"
#include "Ticket.h"
#include "FirstClassVagon.h"
#include "SecondClassVagon.h"
#include "SleepingVagon.h"

#include "DiscountCard.h"
#include "DiscountCardAge.h"
#include "DiscountCardDistance.h"
#include "DiscountCardRoute.h"

void buyTicketDIscountCommand::execute() const
{
	unsigned int trainID;
	std::cin >> trainID;
	manager->cinFailMessage();

	SharedPtr<Train> t = manager->getTrainByID(trainID);
	if (!t)throw std::invalid_argument("Train with such ID does not exist!");

	unsigned int wagonID;
	std::cin >> wagonID;
	manager->cinFailMessage();

	BaseVagon* wagon = t->getVagonByID(wagonID);
	if (!wagon) throw std::invalid_argument("Wagon with such ID does not exist!");

	size_t seat;
	std::cin >> seat;
	manager->cinFailMessage();

	wagon->isFree(seat);

	String ticketFile;
	std::cin >> ticketFile;

	if (!manager->isValidTicketFile(ticketFile)) throw std::invalid_argument("The filename is not in correct form!");

	String cardFile;
	std::cin >> cardFile;
	if (!manager->isValidTicketFile(cardFile)) throw std::invalid_argument("The filename is not in correct form!");
	//mqsto za proverka dali sushtestvuva kartata

	DiscountCard* card = Utility::createDiscountCardFromFirstChar(cardFile);
	
	card->loadDiscountCardFromFile(cardFile);

	String wagonType = wagon->getTypeWagonString();

	unsigned int discount = 0;
	unsigned int price = 0;

	if (wagonType == "First Class") {
		String isFoodIncluded;
		std::cin >> isFoodIncluded;
		bool foodIncluded;

		if (isFoodIncluded == "true") foodIncluded = true;
		else if (isFoodIncluded == "false") foodIncluded = false;
		else throw std::invalid_argument("The food status can be only true or false");

		FirstClassVagon* fc = dynamic_cast<FirstClassVagon*>(wagon);

		price = fc->getBasePrice() * fc->getComforFactor() + (foodIncluded ? 10u : 0u);

		card->applyDiscount(t, price, discount);

		Ticket ticket(t->getStartingStation(), t->getFinalStation(), t->getID(), wagon->getWagonID(), seat, t->getDepartureTime(),
			t->getArrivalTime(), t->getDepartureTrack(), price, discount, ticketFile);

		ticket.saveTicketInFile();

	}
	else if (wagonType == "Second Class") {
		unsigned int kgBagage;
		std::cin >> kgBagage;
		manager->cinFailMessage();

		SecondClassVagon* sc = dynamic_cast<SecondClassVagon*>(wagon);

		price = sc->getBasePrice() + kgBagage * sc->getKgPrice();

		Ticket ticket(t->getStartingStation(), t->getFinalStation(), t->getID(), wagon->getWagonID(), seat, t->getDepartureTime(),
			t->getArrivalTime(), t->getDepartureTrack(), discount, price, ticketFile);

		ticket.saveTicketInFile();
	}
	else if (wagonType == "Sleeping Class") {
		unsigned int distance;
		std::cin >> distance;
		manager->cinFailMessage();

		SleepingVagon* sv = dynamic_cast<SleepingVagon*>(wagon);

		price = sv->getBasePrice() + (sv->getHundredKilometersPrice() / 100) * distance;

		Ticket ticket(t->getStartingStation(), t->getFinalStation(), t->getID(), wagon->getWagonID(), seat, t->getDepartureTime(),
			t->getArrivalTime(), t->getDepartureTrack(), discount, price, ticketFile);

		ticket.saveTicketInFile();
	}
	else throw std::logic_error("Unknown wagon type!");

	wagon->buyPlaceOnSeat(seat);

	std::cout << "Ticket succefully bought for Train ID:" << t->getID() << std::endl;
	std::cout << "Ticket price: " << price << " lv." << std::endl;
	std::cout << "Ticket saved to file: " << ticketFile << std::endl;
}
