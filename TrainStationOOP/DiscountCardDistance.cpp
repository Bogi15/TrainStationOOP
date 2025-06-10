#include "DiscountCardDistance.h"

String DiscountCardDistance::generateFileName() const
{
	String toReturn = ConstantsDCD::CARD_TYPE + this->discountCardHolderName;
	return ConstantsDC::PATH_FOR_DISCOUNT_CARDS + toReturn + ConstantsDC::DISCOUNT_CARD_FILE_SUFFIX;
}

DiscountCardDistance::DiscountCardDistance(String discountCardHolderName, unsigned int discountCardID, unsigned int distance)
	: DiscountCard(discountCardHolderName,discountCardID), distance(distance){}
