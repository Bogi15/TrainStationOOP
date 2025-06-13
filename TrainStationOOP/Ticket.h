#pragma once
#include "String.h"
#include "Utility.h"

class Ticket
{
	Utility myUtility;

	String departingStation;
	String arrivingStation;
	unsigned int trainID;
	unsigned int vagonID;
	unsigned int seatID;
	String departingTime;
	String arrivingTime;
	size_t departingPlatform;
	unsigned int discount;
	unsigned int price;
	String fileName;

public:

	Ticket(String departingStation,
		String arrivingStation,
		unsigned int trainID,
		unsigned int vagonID,
		unsigned int seatID,
		String departingTime,
		String arrivingTime,
		size_t departingPlatform,
		unsigned int discount,
		unsigned int price,
		String fileName);

	void saveTicketInFile()const;

};

