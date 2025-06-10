#pragma once
#include "String.h"
#include "Utility.h"

namespace ConstantsDC {
	constexpr const char* PATH_FOR_DISCOUNT_CARDS = "discountCards/";
    constexpr const char* DISCOUNT_CARD_FILE_SUFFIX = "_Card.dat";
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

	DiscountCard(String discountCardHolderName, unsigned int discountCardID);

	bool validateCard(unsigned int possibleCardID) const;
	virtual void saveDiscountCardToFile() const = 0;
	virtual void loadDiscountCardFromFile() const = 0;
	virtual void printDiscountCard() const = 0;

};

