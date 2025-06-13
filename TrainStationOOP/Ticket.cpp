#include "Ticket.h"
#include "Vector.hpp"

Ticket::Ticket(String departingStation,
			   String arrivingStation,
			   unsigned int trainID,
			   unsigned int vagonID,
			   unsigned int seatID,
			   String departingTime,
			   String arrivingTime,
			   size_t departingPlatform,
			   unsigned int discount,
			   unsigned int price,
			   String fileName)
	: departingStation(departingStation),
	  arrivingStation(arrivingStation),
	  trainID(trainID), 
	  vagonID(vagonID),
	  seatID(seatID), 
	  departingTime(departingTime),
	  arrivingTime(arrivingTime),
	  departingPlatform(departingPlatform),
	  discount(discount),
	  price(price), 
	  fileName(fileName) {
}

void Ticket::saveTicketInFile() const
{
	std::ofstream ofs(fileName.c_str());

	String headline = "Train Ticket";
	String trainIDS = "Train ID: ";
	String IDT(trainID);
	trainIDS += IDT;
	String VagonIDS = "Vagon ID: ";
	String IDV(vagonID);
	VagonIDS += IDV;
	String SeatIDS = "Seat ID: ";
	String IDS(seatID);
	SeatIDS += IDS;
	String departTime = "Departure time: ";
	departTime += departingTime;
	String arriveTime = "Arrival time: ";
	arriveTime += arrivingTime;
	String platform = "Departure platform: ";
	String platID((unsigned int)departingPlatform);
	platform += platID;
	String dis = "Discount: ";
	String money(discount);
	String lv = " lv.";
	dis += money;
	dis += lv;
	String priceS = "Price: ";
	String pr(price);
	priceS += pr;
	priceS += lv;

	ofs << '|' << myUtility.fillWithSign(myUtility.calculateFilling(headline)) << headline << myUtility.fillWithSign(myUtility.calculateFilling(headline)) << "|\n";
	ofs << '|' << trainIDS << myUtility.fillWithSpaces(myUtility.calculateFilling(trainIDS)) << "|\n";
	ofs << '|' << VagonIDS << myUtility.fillWithSpaces(myUtility.calculateFilling(VagonIDS)) << "|\n";
	ofs << '|' << SeatIDS << myUtility.fillWithSpaces(myUtility.calculateFilling(SeatIDS)) << "|\n";
	ofs << '|' << departTime << myUtility.fillWithSpaces(myUtility.calculateFilling(departTime)) << "|\n";
	ofs << '|' << arriveTime << myUtility.fillWithSpaces(myUtility.calculateFilling(arriveTime)) << "|\n";
	ofs << '|' << platform << myUtility.fillWithSpaces(myUtility.calculateFilling(platform)) << "|\n";
	ofs << '|' << dis << myUtility.fillWithSpaces(myUtility.calculateFilling(dis)) << "|\n";
	ofs << '|' << priceS << myUtility.fillWithSpaces(myUtility.calculateFilling(priceS)) << "|\n";
	ofs << '|' << myUtility.fillWithSign(ConstantsU::MAX_LINE_LEN) << myUtility.fillWithSign(ConstantsU::MAX_LINE_LEN) << "|\n";
}
