## **Train Station OOP Console App**

A command‑line application for managing trains, stations, wagons, tickets, and discount cards, implemented in C++ following SOLID principles and custom container/string utilities.

## **Features**

# *Train Management*: create, list, print, and remove trains with customizable departure/arrival times, distance, speed, and platforms.

Wagon Management: add first‑class, second‑class, and sleeping wagons; move wagons between trains; enforce seat occupancy.

Ticketing: buy tickets with per‑wagon and per‑seat pricing, apply discount cards, save tickets to formatted .txt files.

Discount Cards: age‑based, distance‑based, and route‑based cards with polymorphic discount logic.

Station Scheduling: view arriving/departing trains per station, automatically release platforms 30 minutes after departure/arrival.

## **Available Commands**

login <user> <password>

logout

create-train <start> <end> <distance> <speed> <"DD/MM/YYYY HH:MM">

remove-train <trainID>

add-wagon <trainID> <First|Second|Sleeping>

move-wagon <srcTrainID> <wagonID> <dstTrainID>

buy-ticket <trainID> <wagonID> <seat> <filename.txt> [<food|kg|dist>]

print-train <trainID>

print-wagon <trainID> <wagonID>

print-stations

print-schedule <stationName>

create-card <Age|Distance|Route> <param…>

exit
