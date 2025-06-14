#include "DiscountCardAge.h"
#include <fstream>

String DiscountCardAge::generateFileName() const
{
	String toReturn = ConstantsDCA::CARD_TYPE + this->discountCardHolderName;
	return  toReturn + ConstantsDC::DISCOUNT_CARD_FILE_SUFFIX;
}

DiscountCardAge::DiscountCardAge() : DiscountCard(), age(0){}

DiscountCardAge::DiscountCardAge(String discountCardHolderName, unsigned int age)
	: DiscountCard(discountCardHolderName), age(age){}

unsigned int DiscountCardAge::getPercentigeDiscount() const
{
	if (this->age <= 10) return 100;
	else if (this->age >= 11 && this->age <= 18) return 50;
	else return 20;
}

void DiscountCardAge::saveDiscountCardToFile() const
{
	//if (validateCard(this->discountCardID)) return;

	String fileName = generateFileName();
	std::ofstream ofs(fileName.c_str(), std::ios::out | std::ios::trunc);

	if (!ofs) {
		std::cout << "Error opening the file" << std::endl;	
		return;
	}

	String line("Age card");
	String Id(this->discountCardID);
	String age(this->age);
	age += " years old";
	

	ofs << '|' << myUtility.fillWithSign(myUtility.calculateFilling(line)) << line << myUtility.fillWithSign(myUtility.calculateFilling(line)) << "|\n";
	ofs << '|' << this->discountCardHolderName << myUtility.fillWithSpaces(myUtility.calculateFilling(this->discountCardHolderName.c_str())) << "|\n";
	ofs << '|' << age << myUtility.fillWithSpaces(myUtility.calculateFilling(age)) << "|\n";
	ofs << '|' << Id << myUtility.fillWithSpaces(myUtility.calculateFilling(Id)) << "|\n";
	ofs << '|' << myUtility.fillWithSign(ConstantsU::MAX_LINE_LEN) << myUtility.fillWithSign(ConstantsU::MAX_LINE_LEN) << "|\n";
	
	ofs.close();
}

void DiscountCardAge::loadDiscountCardFromFile(const String& fileName)
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

	String age;
	ifs >> age;
	this->age = age.getNumber();

	ifs >> trash;
	ifs >> trash;
	ifs >> trash;

	String id;
	ifs >> id;
	this->discountCardID = id.getNumber();


	ifs >> trash;
	ifs >> trash;
}

void DiscountCardAge::printDiscountCard() const
{
	String line("Age card");
	String Id(this->discountCardID);
	String age(this->age);
	age += " years old";


	std::cout << '|' << myUtility.fillWithSign(myUtility.calculateFilling(line)) << line << myUtility.fillWithSign(myUtility.calculateFilling(line)) << "|\n";
	std::cout << '|' << this->discountCardHolderName << myUtility.fillWithSpaces(myUtility.calculateFilling(this->discountCardHolderName.c_str())) << "|\n";
	std::cout << '|' << age << myUtility.fillWithSpaces(myUtility.calculateFilling(age)) << "|\n";
	std::cout << '|' << Id << myUtility.fillWithSpaces(myUtility.calculateFilling(Id)) << "|\n";
	std::cout << '|' << myUtility.fillWithSign(ConstantsU::MAX_LINE_LEN) << myUtility.fillWithSign(ConstantsU::MAX_LINE_LEN) << "|\n";
}

void DiscountCardAge::getInfoForCard()
{
	String userName;
	std::cin >> userName;
	DiscountCard::setDiscountCardHolderName(userName);

	unsigned int age;
	std::cin >> age;
	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		throw std::invalid_argument("wrong type of data given");
	}
	
	setAge(age);
	
	setDiscountCardID(nextCardID++);
}

void DiscountCardAge::setAge(unsigned int age)
{
	this->age = age;
}

void DiscountCardAge::printFileName() const
{
	std::cout << generateFileName();
}

void DiscountCardAge::applyDiscount(const SharedPtr<Train>& t, unsigned int& price, unsigned int& discount) const
{
	discount = (getPercentigeDiscount() * price)/100;
	price = price - discount;
}
