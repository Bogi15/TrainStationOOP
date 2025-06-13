#pragma once
#include "DiscountCard.h"

namespace ConstantsDCD {
	constexpr const char* CARD_TYPE = "DistanceCard_";
}


class DiscountCardDistance : public DiscountCard
{

protected:
	unsigned int distance;
	unsigned int trainDistance;

	String generateFileName() const;

public:

	DiscountCardDistance(String discountCardHolderName, unsigned int discountCardID, unsigned int distance);
	unsigned int getPercentigeDiscount() const override;

	void saveDiscountCardToFile() const override;
	void loadDiscountCardFromFile(const String& fileName)override;
	void printDiscountCard() const override;

	void setTraintDistance(unsigned int trainDistance);

};

