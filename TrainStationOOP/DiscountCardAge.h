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
	DiscountCardAge(String discountCardHolderName,unsigned int age);

	unsigned int getPercentigeDiscount() const override;
	void saveDiscountCardToFile() const override;
	void loadDiscountCardFromFile(const String& fileName)override;
	void printDiscountCard() const override;

	void getInfoForCard()override;
	void setAge(unsigned int age);
	void printFileName()const override;

	void applyDiscount(const SharedPtr<Train>& t, unsigned int& price, unsigned int& discount)const override;

};

