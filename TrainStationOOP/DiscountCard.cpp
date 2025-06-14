#include "DiscountCard.h"
#include <fstream>
#include <sstream>

unsigned int DiscountCard::nextCardID = 100000;

String DiscountCard::generateFileName() const
{
	return ConstantsDC::DISCOUNT_CARD_FILE_SUFFIX;
}

DiscountCard::DiscountCard()
{
	discountCardHolderName = "";
	discountCardID = 0;
}

DiscountCard::DiscountCard(String discountCardHolderName): discountCardHolderName(discountCardHolderName)
{
	discountCardID = nextCardID++;
}

void DiscountCard::setDiscountCardHolderName(const String& name)
{
	discountCardHolderName = name;
}

void DiscountCard::setDiscountCardID(unsigned int id)
{
	discountCardID = id;
}

unsigned int DiscountCard::getDiscountCardID() const
{
	return discountCardID;
}

void DiscountCard::setNextID(unsigned int id)
{
	nextCardID = id;
}
