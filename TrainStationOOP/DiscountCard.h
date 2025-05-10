#pragma once
#include "String.h"

namespace ConstantsDC {
	constexpr const char* PATH_FOR_DISCOUNT_CARDS = "discountCards/";
    constexpr const char* DISCOUNT_CARD_FILE_SUFFIX = "Card.dat";
}

class DiscountCard
{
protected:
	String discountCardHolderName;
	unsigned int discountCardID;

public:

	DiscountCard(String discountCardHolderName, unsigned int discountCardID);

	bool validateCard() const;
	virtual void saveDiscountCardToFile() const = 0;
	virtual void loadDiscountCardFromFile() const = 0;
	virtual void printDiscountCard() const = 0;
};

