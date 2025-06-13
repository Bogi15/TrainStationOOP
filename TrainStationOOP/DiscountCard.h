#pragma once
#include "String.h"
#include "Utility.h"

namespace ConstantsDC {
	constexpr const char* PATH_FOR_DISCOUNT_CARDS = "discountCards\\";
    constexpr const char* DISCOUNT_CARD_FILE_SUFFIX = "_Card.txt";
	constexpr const char* DISCOUNT_CARDS_ID_HOLDER = ".txt";
}

class DiscountCard
{
private:
	String generateFileName() const;
	String genereateStringID() const;

protected:
	String discountCardHolderName;
	unsigned int discountCardID;
	size_t numberOfCardsCreated;
	Utility myUtility;

public:

	DiscountCard();
	DiscountCard(String discountCardHolderName, unsigned int discountCardID);

	bool validateCard(unsigned int possibleCardID) const;
	virtual void saveDiscountCardToFile() const = 0;
	virtual void loadDiscountCardFromFile(const String& fileName) = 0;
	virtual void printDiscountCard() const = 0;
	virtual unsigned int getPercentigeDiscount() const = 0;

};

