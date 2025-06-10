#include "DiscountCard.h"
#include <fstream>

String DiscountCard::generateFileName() const
{
	return ConstantsDC::DISCOUNT_CARDS_ID_HOLDER;
}

String DiscountCard::genereateStringID() const
{
	
	
}

DiscountCard::DiscountCard(String discountCardHolderName, unsigned int discountCardID) : discountCardHolderName(discountCardHolderName), discountCardID(discountCardID)
{
}

bool DiscountCard::validateCard(unsigned int possibleCardID) const
{
	if (possibleCardID > 999999 || possibleCardID < 100000) return false;

	String fileName = generateFileName();
	std::ifstream ifs(fileName.c_str(), std::ios::binary);

	ifs.read((char*)&this->numberOfCardsCreated, sizeof(this->numberOfCardsCreated));

	for (size_t i = 0;i < this->numberOfCardsCreated;i++) {
		unsigned int fromFileID;
		ifs.read((char*)&fromFileID, sizeof(fromFileID));

		if (fromFileID == possibleCardID) {
			ifs.close();
			return true;
		}

		ifs.close();
		return false;
	}
}
