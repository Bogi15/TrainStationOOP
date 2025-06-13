#include <iostream>
#include "FirstClassVagon.h"
#include "SecondClassVagon.h"
#include "SleepingVagon.h"
#include "DiscountCardAge.h"
#include "DiscountCardRoute.h"
#include "DiscountCardDistance.h"
#include "Train.h"
#include "Ticket.h"
#include "Station.h"
#include "Shared_Weak_Ptr.hpp"
#include "systemManager.h"
#include "App.h"

int main() {
	FirstClassVagon a(20,0.9);
	SecondClassVagon b(20, 10);
	SleepingVagon c(20,15);
	a.printUnoccupiedSeats();
	std::cout << a.getWagonID() << std::endl;
	b.printUnoccupiedSeats();
	std::cout << b.getWagonID() << std::endl;
	c.printUnoccupiedSeats();
	std::cout << c.getWagonID() << std::endl;

	String name = "Ivan_Petrov";
	DiscountCardAge d(name, 222222, 15);
	d.saveDiscountCardToFile();
	String name2 = "petar";
	DiscountCardAge e(name2, 111111, 12);
	String file = "discountCards\\AgeCard_Ivan_Petrov_Card.txt";
	e.loadDiscountCardFromFile(file);
	

	DiscountCardDistance f("Georgi_Pavlov", 333333, 300);
	f.saveDiscountCardToFile();

	DiscountCardDistance g(name, 111111, 10);
	g.loadDiscountCardFromFile("discountCards\\DistanceCard_Georgi_Pavlov_Card.txt");

	DiscountCardRoute h("Boriskata",  555555 , "Velikoto_tarnovo");
	h.saveDiscountCardToFile();
	DiscountCardRoute l("h", 999999, "a");
	l.loadDiscountCardFromFile("discountCards\\RouteCard_Boriskata_Card.txt");
	l.printDiscountCard();

	//Train t("Sofia", "Varna", 300, 150, "08/06/2025 17:30");
	//t.addVagon(a);
	//t.addVagon(b);
	//t.addVagon(c);

	//Station s("Gabrovo");
	//SharedPtr<Train> sPTR(new Train("Varna", "Sofia", 450, 150, "09/06/2025 23:32"));
	//s.addArrivingTrain(sPTR);
	//s.addDepartingTrain(sPTR);
	

	//t.getSeat(3, 3);
	////t.getSeat(3, 3);
	//t.printVagons();

	String aa = "Sofia";
	String ab = "Varna";

	Ticket Edin(aa, ab, 2001, 1, 9, "11/06/2025 08:00", "11/06/2025 12:00", 1, 50, 0,"ticket1.txt");
	Edin.saveTicketInFile();

	//t.printTrain();
	//Train t1 = t;
	//t1.printTrain();
	//c.printWagon();
	//a.printWagon();
	//b.printWagon();

	//s.printSchedule();
	//s.printTrainsByDestination("Sofia");
	//s.printTrainsByTime("09/06/2025", "23:06");
	//
	//SharedPtr<Train> tPTR(sPTR);
	//systemManager m;
	//m.addStation(s);
	//m.addTrain(tPTR, s);
	//m.addTrain(tPTR, s);
	//m.addTrain(tPTR, s);
	//m.saveAllData();
	//m.loadAllData();
	//m.getAllStations()[0].printTrackStatus();

	//std::ofstream ofs("admins.bin", std::ios::binary);
	//size_t number = 1;
	//String nameForFile = "admin";
	//String passwordForFile = "password";
	//ofs.write((const char*)&number, sizeof(size_t));
	//nameForFile.writeBinary(ofs);
	//passwordForFile.writeBinary(ofs);

	//std::ofstream ofs("stations.bin", std::ios::binary);

	//size_t numberOfStations = 0;
	//ofs.write((const char*)&numberOfStations, sizeof(size_t));


	App application;
	application.run();
}