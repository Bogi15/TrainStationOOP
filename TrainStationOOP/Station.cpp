#include "Station.h"

Station::Station(String stationName) : stationName(stationName)
{

}

const String& Station::getStationName() const
{
	return this->stationName;
}
