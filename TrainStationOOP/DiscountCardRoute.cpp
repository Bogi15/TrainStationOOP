#include "DiscountCardRoute.h"
#include "Train.h"

String DiscountCardRoute::generateFileName() const
{
	String toReturn = ConstantsDCR::CARD_TYPE + this->discountCardHolderName;
	return toReturn + ConstantsDC::DISCOUNT_CARD_FILE_SUFFIX;
}

DiscountCardRoute::DiscountCardRoute(String discountCardHolderName, String destionation)
		:DiscountCard(discountCardHolderName), destination(destionation){}

unsigned int DiscountCardRoute::getPercentigeDiscount() const
{
	return 0;
}

void DiscountCardRoute::saveDiscountCardToFile() const
{
	String fileName = generateFileName();
	std::ofstream ofs(fileName.c_str(), std::ios::out | std::ios::trunc);

	if (!ofs) {
		std::cout << "Error opening the file" << std::endl;
		return;
	}

	String line("Route card");
	String Id(this->discountCardID);
	String destination(this->destination);


	ofs << '|' << myUtility.fillWithSign(myUtility.calculateFilling(line)) << line << myUtility.fillWithSign(myUtility.calculateFilling(line)) << "|\n";
	ofs << '|' << this->discountCardHolderName << myUtility.fillWithSpaces(myUtility.calculateFilling(this->discountCardHolderName.c_str())) << "|\n";
	ofs << '|' << destination << myUtility.fillWithSpaces(myUtility.calculateFilling(destination)) << "|\n";
	ofs << '|' << Id << myUtility.fillWithSpaces(myUtility.calculateFilling(Id)) << "|\n";
	ofs << '|' << myUtility.fillWithSign(ConstantsU::MAX_LINE_LEN) << myUtility.fillWithSign(ConstantsU::MAX_LINE_LEN) << "|\n";

	ofs.close();
}

void DiscountCardRoute::loadDiscountCardFromFile(const String& fileName)
{
	std::ifstream ifs(fileName.c_str());

	if (!ifs) {
		std::cout << "Error opening the file: " << fileName << std::endl;
		return;
	}

	String trash;
	ifs >> trash;
	ifs >> trash;

	String name;
	ifs >> name;
	ifs >> trash;

	name = name.stripSign();
	//name.trim();
	this->discountCardHolderName = name;

	String destination;
	ifs >> destination;
	this->destination = destination.stripSign();

	ifs >> trash;

	String id;
	ifs >> id;
	this->discountCardID = id.getNumber();


	ifs >> trash;
	ifs >> trash;

}

void DiscountCardRoute::printDiscountCard() const
{
	String line("Route card");
	String Id(this->discountCardID);
	String destination(this->destination);

	std::cout << '|' << myUtility.fillWithSign(myUtility.calculateFilling(line)) << line << myUtility.fillWithSign(myUtility.calculateFilling(line)) << "|\n";
	std::cout << '|' << this->discountCardHolderName << myUtility.fillWithSpaces(myUtility.calculateFilling(this->discountCardHolderName.c_str())) << "|\n";
	std::cout << '|' << destination << myUtility.fillWithSpaces(myUtility.calculateFilling(destination)) << "|\n";
	std::cout << '|' << Id << myUtility.fillWithSpaces(myUtility.calculateFilling(Id)) << "|\n";
	std::cout << '|' << myUtility.fillWithSign(ConstantsU::MAX_LINE_LEN) << myUtility.fillWithSign(ConstantsU::MAX_LINE_LEN) << "|\n";

}

void DiscountCardRoute::setDestination(const String& destination)
{
	this->destination = destination;
}


void DiscountCardRoute::getInfoForCard()
{
	String userName;
	std::cin >> userName;
	DiscountCard::setDiscountCardHolderName(userName);

	String destination;
	std::cin >> destination;
	setDestination(destination);

	setDiscountCardID(nextCardID++);
}

void DiscountCardRoute::printFileName() const
{
	std::cout << generateFileName();
}

void DiscountCardRoute::applyDiscount(const SharedPtr<Train>& t, unsigned int& price, unsigned int& discount) const
{
	if (destination == t->getFinalStation()) {
		discount = price;
		price = 0;
	}
}
