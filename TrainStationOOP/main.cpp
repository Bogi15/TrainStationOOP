#include <iostream>
#include "FirstClassVagon.h"
#include "SecondClassVagon.h"
#include "SleepingVagon.h"

int main() {
	FirstClassVagon a(20,0.9);
	SecondClassVagon b(20, 10);
	SleepingVagon c(20,15);
	a.printUnoccupiedSeats();
	std::cout << a.getVagonID() << std::endl;
	b.printUnoccupiedSeats();
	std::cout << b.getVagonID() << std::endl;
	c.printUnoccupiedSeats();
	std::cout << c.getVagonID() << std::endl;


}