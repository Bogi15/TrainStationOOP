#pragma once
#include "String.h"
#include "String.h"
#include "VagonType.h"      
#include "BaseVagon.h"      
#include "FirstClassVagon.h"
#include "SecondClassVagon.h"
#include "SleepingVagon.h"

namespace ConstantsU {
	constexpr int MAX_LINE_LEN = 34;
}

class Utility
{

public:

	static void fillWithDashSign(size_t len);
	String fillWithSign(size_t len) const;
	String fillWithSpaces(size_t len) const;
	size_t calculateFilling(const String& str)const;


	static std::tm parseDateTime(const String& s);
	static std::time_t toTimeT(const std::tm& tm);

	static BaseVagon* create(VagonType tag);
	static BaseVagon* readFromStream(std::ifstream& ifs);
	
	static bool isValidDate(const String& date);
	static bool isValidHour(const String& time);
	static bool isTimeToFree(const String& t);
};

