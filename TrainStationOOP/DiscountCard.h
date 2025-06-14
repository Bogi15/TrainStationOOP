#pragma once
#include "String.h"
#include "Utility.h"
#include "Shared_Weak_Ptr.hpp"

class Train;
class BaseVagon;

namespace ConstantsDC {
    constexpr const char* DISCOUNT_CARD_FILE_SUFFIX = ".txt";
}

class DiscountCard
{
private:
	String generateFileName() const;

protected:
	String discountCardHolderName;
	unsigned int discountCardID;
	Utility myUtility;

	static unsigned int nextCardID;

public:

	DiscountCard();
	DiscountCard(String discountCardHolderName);

	void setDiscountCardHolderName(const String& name);
	void setDiscountCardID(unsigned int id);

	virtual void saveDiscountCardToFile() const = 0;
	virtual void loadDiscountCardFromFile(const String& fileName) = 0;
	virtual void printDiscountCard() const = 0;

	virtual unsigned int getPercentigeDiscount() const = 0;
	unsigned int getDiscountCardID()const;
	static void setNextID(unsigned int id);

	virtual void getInfoForCard() = 0;
	virtual void printFileName()const = 0;
	virtual void applyDiscount(const SharedPtr<Train>& t, unsigned int& price, unsigned int& discount)const = 0;

};

