#include "Utility.h"

String Utility::fillWithSign(size_t len) const
{
    len /= 2;
    String toReturn("");
    while (len) {
        toReturn += "=";
    }

    return toReturn;
}

String Utility::fillWithSpaces(size_t len) const
{

    String toReturn("");
    while (len) {
        toReturn += " ";
    }

    return toReturn;
}

size_t Utility::calculateFilling(const String& str) const
{
    return ConstantsU::MAX_LINE_LEN - str.getSize();
}
