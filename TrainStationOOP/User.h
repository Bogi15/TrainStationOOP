#pragma once
#include "String.h"
#include "Vector.hpp"
#include "Station.h"



class User
{
public:
    User() = default;

	 void printStations(const Vector<Station>& stations) const;
     void printSchedule(const Station& station) const;
     void printScheduleToDestination(const Station& station, const String& destination) const;
     void printScheduleAfterTime(const Station& station, const String& date, const String& time) const;
     void printTrainInfo(const Train& train) const;
     void printWagonInfo(const Train& train, int wagonID) const;
     void buyTicket(Train& train, unsigned int vagonID, size_t seat, const String& ticketFileName,
        const Vector<String>& extraParams) const;
     void buyTicket(Train& train, unsigned int vagonID, size_t seat, const String& ticketFileName,
        const String& discountCardFile ,Vector <String>& extraParams) const;

     virtual bool isAdmin()const;
     virtual void writeBinary(std::ofstream& ofs) const = 0;
     virtual void readBinary(std::ifstream& ifs) = 0;


     ~User() = default;
};

