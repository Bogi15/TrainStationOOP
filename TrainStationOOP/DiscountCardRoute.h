#pragma once
#include "DiscountCard.h"

namespace ConstantsDCR {
	constexpr const char* CARD_TYPE = "RouteCard_";
}

class DiscountCardRoute : public DiscountCard
{
protected:
	String destination;

	String generateFileName() const;

public:

	DiscountCardRoute() = default;
	DiscountCardRoute(String discountCardHolderName, String destionation);
	unsigned int getPercentigeDiscount() const override;

	void saveDiscountCardToFile() const override;
	void loadDiscountCardFromFile(const String& fileName)override;
	void printDiscountCard() const override;

	void setDestination(const String& destination);

	void getInfoForCard()override;
	void printFileName()const override;
	void applyDiscount(const SharedPtr<Train>& t, unsigned int& price, unsigned int& discount)const override;

};

