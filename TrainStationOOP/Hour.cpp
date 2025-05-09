#include "Hour.h"

Hour::Hour(size_t hour, size_t minute)
{
    this->hour = hour;
    this->minute = minute;
}

size_t Hour::getHour() const
{
    return this->hour;
}

size_t Hour::getMinute() const
{
    return this->minute;
}

void Hour::setHour(size_t hour)
{
    this->hour = hour;
}

void Hour::setMinute(size_t minute)
{
    this->minute = minute;
}
