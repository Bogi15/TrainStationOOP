#include "Day.h"

Day::Day(size_t day, size_t month, size_t year)
{
    this->day = day;
    this->month = month;
    this->year = year;
}

size_t Day::getDay() const
{
    return this->day;
}

size_t Day::getMonth() const
{
    return  this->month;
}

size_t Day::getYear() const
{
    return this->year;
}

void Day::setDay(size_t day)
{
    this->day = day;
}

void Day::setMonth(size_t month)
{
    this->month = month;
}

void Day::setYear(size_t year)
{
    this->year = year;
}
