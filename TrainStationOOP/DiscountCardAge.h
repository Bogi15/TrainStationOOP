#pragma once
#include "DiscountCard.h"

namespace ConstantsDCA {
	constexpr const char* CARD_TYPE = "AgeCard_";
}

class DiscountCardAge : public DiscountCard
{
private:
	unsigned int age;

	String generateFileName() const;

public:
	DiscountCardAge();
	DiscountCardAge(String discountCardHolderName, unsigned int discountCardID ,unsigned int age);

	unsigned int getPercentigeDiscount() const override;
	void saveDiscountCardToFile() const override;
	void loadDiscountCardFromFile(const String& fileName)override;
	void printDiscountCard() const override;
};

