#pragma once
#include "String.h"

namespace ConstantsU {
	constexpr int MAX_LINE_LEN = 30;
}

class Utility
{

public:

	String fillWithSign(size_t len) const;
	String fillWithSpaces(size_t len) const;
	size_t calculateFilling(const String& str)const;
	
};

