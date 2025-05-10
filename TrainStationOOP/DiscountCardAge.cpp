#include "DiscountCardAge.h"
#include <istream>

String DiscountCardAge::generateFileName() const
{
	return ConstantsDC::PATH_FOR_DISCOUNT_CARDS + this->discountCardHolderName + ConstantsDC::DISCOUNT_CARD_FILE_SUFFIX;
}

DiscountCardAge::DiscountCardAge(String discountCardHolderName, unsigned int discountCardID, unsigned int age) : DiscountCard(discountCardHolderName,discountCardID), age(age)
{
}

unsigned int DiscountCardAge::getPercentigeDiscount() const
{
	if (this->age <= 10) return 100;
	else if (this->age >= 11 && this->age <= 18) return 50;
	else return 20;
}

void DiscountCardAge::saveDiscountCardToFile() const
{
	String fileName = generateFileName();
	std::ofstream ofs(fileName.c_str(), std::ios::binary);

	if (!ofs) {
		std::cout << "Error opening the file" << std::endl;	
		return;
	}

	size_t sizeOfDiscountCardHolderName = this->discountCardHolderName.getSize() + 1;

	ofs.write((const char*)(&sizeOfDiscountCardHolderName), sizeof(sizeOfDiscountCardHolderName));
	ofs.write(this->discountCardHolderName.c_str(), sizeof(this->discountCardHolderName));
	ofs.write((const char*)(&this->discountCardID), sizeof(this->discountCardID));
	ofs.write((const char*)(&this->age), sizeof(this->age));

	ofs.close();
}

void DiscountCardAge::loadDiscountCardFromFile() const
{
	String fileName = generateFileName();
	std::ifstream ifs(fileName.c_str(), std::ios::binary);

	if (!ifs) {
		std::cout << "Error opening the file" << std::endl;
		return;
	}

	size_t sizeOfDiscountCardHolderName;
	
}
