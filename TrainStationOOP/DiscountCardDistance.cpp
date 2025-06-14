#include "DiscountCardDistance.h"
#include "Train.h"

String DiscountCardDistance::generateFileName() const
{
	String toReturn = ConstantsDCD::CARD_TYPE + this->discountCardHolderName;
	return toReturn + ConstantsDC::DISCOUNT_CARD_FILE_SUFFIX;
}

DiscountCardDistance::DiscountCardDistance(String discountCardHolderName, unsigned int distance)
	: DiscountCard(discountCardHolderName), distance(distance){}

unsigned int DiscountCardDistance::getPercentigeDiscount() const
{
	return distance < trainDistance ? 50 : 30;
}

void DiscountCardDistance::saveDiscountCardToFile() const
{
	String fileName = generateFileName();
	std::ofstream ofs(fileName.c_str(), std::ios::out | std::ios::trunc);

	if (!ofs) {
		std::cout << "Error opening the file" << std::endl;
		return;
	}

	String line("Distance  card");
	String Id(this->discountCardID);
	String distance(this->distance);
	distance += " km";


	ofs << '|' << myUtility.fillWithSign(myUtility.calculateFilling(line)) << line << myUtility.fillWithSign(myUtility.calculateFilling(line)) << "|\n";
	ofs << '|' << this->discountCardHolderName << myUtility.fillWithSpaces(myUtility.calculateFilling(this->discountCardHolderName.c_str())) << "|\n";
	ofs << '|' << distance << myUtility.fillWithSpaces(myUtility.calculateFilling(distance)) << "|\n";
	ofs << '|' << Id << myUtility.fillWithSpaces(myUtility.calculateFilling(Id)) << "|\n";
	ofs << '|' << myUtility.fillWithSign(ConstantsU::MAX_LINE_LEN) << myUtility.fillWithSign(ConstantsU::MAX_LINE_LEN) << "|\n";

	ofs.close();
}

void DiscountCardDistance::loadDiscountCardFromFile(const String& fileName)
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

	String distance;
	ifs >> distance;
	this->distance = distance.getNumber();

	ifs >> trash;
	ifs >> trash;

	String id;
	ifs >> id;
	this->discountCardID = id.getNumber();


	ifs >> trash;
	ifs >> trash;
}

void DiscountCardDistance::printDiscountCard() const
{

	String line("Distance  card");
	String Id(this->discountCardID);
	String distance(this->distance);
	distance += " km";

	std::cout << '|' << myUtility.fillWithSign(myUtility.calculateFilling(line)) << line << myUtility.fillWithSign(myUtility.calculateFilling(line)) << "|\n";
	std::cout << '|' << this->discountCardHolderName << myUtility.fillWithSpaces(myUtility.calculateFilling(this->discountCardHolderName.c_str())) << "|\n";
	std::cout << '|' << distance << myUtility.fillWithSpaces(myUtility.calculateFilling(distance)) << "|\n";
	std::cout << '|' << Id << myUtility.fillWithSpaces(myUtility.calculateFilling(Id)) << "|\n";
	std::cout << '|' << myUtility.fillWithSign(ConstantsU::MAX_LINE_LEN) << myUtility.fillWithSign(ConstantsU::MAX_LINE_LEN) << "|\n";

}

void DiscountCardDistance::setTraintDistance(unsigned int trainDistance)
{
	this->trainDistance = trainDistance;
}

void DiscountCardDistance::getInfoForCard()
{

	String userName;
	std::cin >> userName;
	DiscountCard::setDiscountCardHolderName(userName);

	unsigned int distance;
	std::cin >> distance;
	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		throw std::invalid_argument("wrong type of data given");
	}

	setDistance(distance);

	setDiscountCardID(nextCardID++);
}

void DiscountCardDistance::setDistance(unsigned int distance)
{
	this->distance = distance;
}

void DiscountCardDistance::printFileName() const
{
	std::cout << generateFileName();
}

void DiscountCardDistance::applyDiscount(const SharedPtr<Train>& t,unsigned int& price, unsigned int& discount) const
{
	if (t->getDistance() <= distance) {
		discount = price * 0.5;
		price = price - discount;
	}
	else {
		discount = price * 0.3;
		price = price - discount;
	}
}
