#include <iostream>
#include "FirstClassVagon.h"
#include "SecondClassVagon.h"
#include "SleepingVagon.h"

int main() {
	FirstClassVagon a(20,0.9);
	SecondClassVagon b(20, 10);
	SleepingVagon c(20,15);
	a.printUnoccupiedSeats();
	b.printUnoccupiedSeats();
	c.printUnoccupiedSeats();

}