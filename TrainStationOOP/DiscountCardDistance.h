#pragma once
#include "DiscountCard.h"

namespace ConstantsDCD {
	constexpr const char* CARD_TYPE = "DistanceCard_";
}


class DiscountCardDistance : public DiscountCard
{
protected:
	unsigned int distance;

	String generateFileName() const;

public:

	DiscountCardDistance(String discountCardHolderName, unsigned int discountCardID, unsigned int distance);


};

