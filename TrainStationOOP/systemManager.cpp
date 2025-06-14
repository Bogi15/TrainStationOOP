#include "systemManager.h"
#include "OrdinaryUser.h"
#include "Utility.h"

User* systemManager::currentUser = nullptr;

systemManager::systemManager()
{
}

void systemManager::saveAllData() const
{
    data.saveAllAdminsInFile();
    data.saveAllTrainsInFile();
    data.saveAllStationsInFile();
    data.saveAllCardsIDs();
}

void systemManager::loadAllData()
{
    data.loadAllAdminsFromFile();
    data.loadAllTrainsFromFile();
    data.loadAllStationsFromFile();
    data.loadAllCardsIDs();
}

void systemManager::addStation(const Station& s)
{
    data.addStation(s);
}

void systemManager::addTrain(const SharedPtr<Train>& t, Station& s)
{
    size_t trackIdx;
    

    if (!s.reserveTrack(trackIdx)) {
        std::cout << "No available departure tracks at station " << s.getStationName() << "\n";
        return;
    }

    t->setDepartureTrack(trackIdx);
    std::cout << "Successfully reserved departure track #" << trackIdx + 1 << " at station " << s.getStationName() << "\n";

    data.addTrain(t);
}

void systemManager::addCardID(unsigned int id)
{
    data.addCardID(id);
}

bool systemManager::removeTrain(SharedPtr<Train> t)
{
    return data.removeTrain(t);
}

void systemManager::freeTracks()
{
    for (size_t i = 0;i < data.getAllTrains().getSize();i++) {
        String departTime = data.getAllTrains()[i]->getDepartureTime();
        String arriveTime = data.getAllTrains()[i]->getArrivalTime();

        if (Utility::isTimeToFree(departTime)) {
            Station& s = getStationByName(data.getAllTrains()[i]->getStartingStation());
            s.releaseTrack(data.getAllTrains()[i]->getDepartureTrack());
        }

        if (Utility::isTimeToFree(arriveTime)) {
            Station& s = getStationByName(data.getAllTrains()[i]->getFinalStation());
            s.releaseTrack(data.getAllTrains()[i]->getArrivalTrack());
        }
    }
}

const SharedPtr<Train> systemManager::getTrainByID(unsigned int id) const
{
    return data.getTrainByID(id);
}

const Station& systemManager::getStationByName(const String& name) const
{
    return data.getStationByName(name);
}

Station& systemManager::getStationByName(const String& name)
{
    return data.getStationByName(name);
}

const Vector<Station>& systemManager::getAllStations() const
{
    return data.getAllStations();
}

Vector<Station>& systemManager::getAllStations()
{
    return data.getAllStations();
}

const User* systemManager::getUser() const
{
    return currentUser;
}

const Vector<User*>& systemManager::getAllAdmins() const
{
    return data.getAllAdmins();
}

Vector<User*>& systemManager::getAllAdmins()
{
    return data.getAllAdmins();
}

const Vector<SharedPtr<Train>>& systemManager::getAllTrains() const
{
    return data.getAllTrains();
}

Vector<SharedPtr<Train>>& systemManager::getAllTrains()
{
    return data.getAllTrains();
}


void systemManager::setUser(User*& user)
{
    currentUser = user;
}

bool systemManager::containsStation(const String& name)
{
    for (size_t i = 0;i < data.getAllStations().getSize();i++) {
        if (data.getAllStations()[i].getStationName() == name) return true;
    }

    return false;
}

bool systemManager::isValidWagonID(const SharedPtr<Train>& t, unsigned int wagonID)
{
    for (size_t i = 0;i < t->getVagons().getSize();i++) {
        if (t->getVagons()[i]->getWagonID() == wagonID) return true;
    }

    return false;
}

bool systemManager::isValidCardType(const String& type) const
{
    if (type == "route-card")
        return true;
    else if (type == "age-card")
        return true;
    else if (type == "distance-card")
        return true;
    else return false;
}

bool systemManager::isValidCardID(unsigned int ID) const
{
    for (size_t i = 0;i < data.getAllDiscountCardIDs().getSize();i++) {
        if (data.getAllDiscountCardIDs()[i] == ID) return true;
    }

    return false;
}

bool systemManager::isValidTicketFile(const String& fileName) const
{
    String suffix = ".txt";;
    size_t n = fileName.getSize();
    size_t m = suffix.getSize();

    if (n < m) return false;

    String fileSuffix = fileName.substr(n - m, m);

    return (fileSuffix == suffix);
}

void systemManager::cinFailMessage() const
{
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::invalid_argument("wrong type of data given");
    }
}

void systemManager::reserveTrackForTrain(Station& s)
{
    bool isReserved = false;
    for (size_t i = 0;i < s.getNumberOfTracks();i++) {
        if (s.reserveTrack(i)) {
            isReserved = true;
            break;
        }
    }
    
    if (isReserved) std::cout << "Successfully reserved tracks for the train" << std::endl;
    else "No available tracks";
}

void systemManager::printStations() const
{
    std::cout << "===Stations===" << std::endl;
    for (size_t i = 0;i < data.getAllStations().getSize();i++) {
        std::cout << i + 1 << ":" << data.getAllStations()[i].getStationName() << std::endl;
    }
    std::cout << std::endl;
}

systemManager::~systemManager()
{
}
