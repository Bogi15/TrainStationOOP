#pragma once
#include "DiscountCard.h"

namespace ConstantsDCR {
	constexpr const char* CARD_TYPE = "RouteCard_";
}

class DiscountCardRoute : public DiscountCard
{
protected:
	String destination;
	String trainDestination;

	String generateFileName() const;

public:

	DiscountCardRoute(String discountCardHolderName, unsigned int discountCardID, String destionation);
	unsigned int getPercentigeDiscount() const override;

	void saveDiscountCardToFile() const override;
	void loadDiscountCardFromFile(const String& fileName)override;
	void printDiscountCard() const override;

	void setTrainDestination(const String& trainDestination);

};

