#include "DiscountCardAge.h"
#include <istream>

String DiscountCardAge::generateFileName() const
{
	String toReturn = ConstantsDCA::CARD_TYPE + this->discountCardHolderName;
	return ConstantsDC::PATH_FOR_DISCOUNT_CARDS + toReturn +ConstantsDC::DISCOUNT_CARD_FILE_SUFFIX;
}

DiscountCardAge::DiscountCardAge(String discountCardHolderName, unsigned int discountCardID, unsigned int age)
	: DiscountCard(discountCardHolderName,discountCardID), age(age){}

unsigned int DiscountCardAge::getPercentigeDiscount() const
{
	if (this->age <= 10) return 100;
	else if (this->age >= 11 && this->age <= 18) return 50;
	else return 20;
}

void DiscountCardAge::saveDiscountCardToFile() const
{
	if (validateCard(this->discountCardID)) return;

	String fileName = generateFileName();
	std::ofstream ofs(fileName.c_str());

	if (!ofs) {
		std::cout << "Error opening the file" << std::endl;	
		return;
	}

	String line("Age card");
	String Id(this->discountCardID);
	String age(this->age);
	age += " years old";
	String firstLine("Age card");

	ofs << '|' << myUtility.fillWithSign(myUtility.calculateFilling(line)) << line << myUtility.fillWithSign(myUtility.calculateFilling(line)) << '|' << std::endl;
	ofs << '|' << this->discountCardHolderName << myUtility.fillWithSpaces(myUtility.calculateFilling(this->discountCardHolderName)) << '|' << std::endl;
	ofs << '|' << age << myUtility.fillWithSpaces(myUtility.calculateFilling(age)) << '|' << std::endl;
	ofs << '|' << Id << myUtility.fillWithSpaces(myUtility.calculateFilling(Id)) << '|' << std::endl;
	ofs << '|' << myUtility.fillWithSign(ConstantsU::MAX_LINE_LEN) << '|' << std::endl;
	
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
