#include "stationsRepository.h"
#include "Admin.h"
#include "Utility.h"

Vector<Station> stationsRepository::allStations{};
Vector<SharedPtr<Train>> stationsRepository::allTrains{};

const Vector<Station>& stationsRepository::getAllStations() const
{
    return allStations;
}

Vector<Station>& stationsRepository::getAllStations()
{
    return allStations;
}

const Vector<SharedPtr<Train>>& stationsRepository::getAllTrains() const
{
    return allTrains;
}

Vector<SharedPtr<Train>>& stationsRepository::getAllTrains()
{
    return allTrains;
}

SharedPtr<Train> stationsRepository::getTrainByID(unsigned int id) const
{
    for (size_t i = 0;i < allTrains.getSize();i++) {
        if (allTrains[i]->getID() == id) return allTrains[i];
    }

    return SharedPtr<Train>(nullptr);
    //throw std::out_of_range("There is no train with such ID");
}

Vector<User*>& stationsRepository::getAllAdmins()
{
    return admins;
}

const Vector<User*>& stationsRepository::getAllAdmins() const
{
    return admins;
}

const Vector<unsigned int> stationsRepository::getAllDiscountCardIDs() const
{
    return discountCardIDs;
}

const Station& stationsRepository::getStationByName(const String& name) const
{
    for (size_t i = 0;i < allStations.getSize();i++) {
        if (allStations[i].getStationName() == name) return allStations[i];
    }

    throw std::logic_error("The station does not exist!");
}

Station& stationsRepository::getStationByName(const String& name)
{
    for (size_t i = 0;i < allStations.getSize();i++) {
        if (allStations[i].getStationName() == name) return allStations[i];
    }

    throw std::logic_error("The station does not exist!");
}

void stationsRepository::addTrain(const SharedPtr<Train>& t)
{

    allTrains.push_back(t);
}

void stationsRepository::addStation(const Station& s)
{
    allStations.push_back(s);
}

void stationsRepository::addCardID(unsigned int id)
{
    discountCardIDs.push_back(id);
}

bool stationsRepository::removeTrain(SharedPtr<Train> t)
{
    for (size_t i = 0;i < allTrains.getSize();i++) {
        if (allTrains[i]->getID() == t->getID()) {
            allTrains.remove(i);
            return true;
        }
    }

    return false;
}

void stationsRepository::saveAllStationsInFile() const
{
    std::ofstream ofs(namesOfFiles::allStationsFile, std::ios::binary);

    size_t numberOfStations = allStations.getSize();
    ofs.write((const char*)&numberOfStations, sizeof(size_t));

    for (size_t i = 0;i < numberOfStations;i++) {
        allStations[i].writeStationBinary(ofs);
    }
}

void stationsRepository::loadAllStationsFromFile()
{
    std::ifstream ifs(namesOfFiles::allStationsFile, std::ios::binary);

    if (!ifs) {
        return;
    }

    size_t numberOfStations;
    ifs.read((char*)&numberOfStations, sizeof(size_t));

    allStations.clear();

    for (size_t i = 0;i < numberOfStations;i++) {
        Station s;
        s.readStationBinary(ifs);
        allStations.push_back(s);
    }
}

void stationsRepository::saveAllTrainsInFile() const
{
    std::ofstream ofs(namesOfFiles::allTrainsFile, std::ios::binary);

    unsigned int lastID = Train::getNextID();
    ofs.write((const char*)&lastID, sizeof(unsigned int));

    size_t numberOfTrains = allTrains.getSize();
    ofs.write((const char*)&numberOfTrains, sizeof(size_t));

    

    for (size_t i = 0;i < numberOfTrains;i++) {
        allTrains[i]->writeTrainBinary(ofs);
    }
}

void stationsRepository::loadAllTrainsFromFile()
{
    std::ifstream ifs(namesOfFiles::allTrainsFile, std::ios::binary);
    if (!ifs) {
        return;
    }

    unsigned int lastID;
    ifs.read((char*)&lastID, sizeof(unsigned int));
    Train::setNextID(lastID);

    size_t numberOfTrains;
    ifs.read((char*)&numberOfTrains, sizeof(size_t));

    allTrains.clear();

    for (size_t i = 0;i < numberOfTrains;i++) {
        SharedPtr<Train> t(new Train());
        t->readTrainBinary(ifs);
        allTrains.push_back(t);
    }
}

void stationsRepository::saveAllAdminsInFile() const
{
    std::ofstream ofs(namesOfFiles::allAdminsFile, std::ios::binary);

    size_t numberOfAdmins = admins.getSize();
    ofs.write((const char*)&numberOfAdmins, sizeof(size_t));

    for (size_t i = 0;i < numberOfAdmins;i++) {
        admins[i]->writeBinary(ofs);
    }
}

void stationsRepository::loadAllAdminsFromFile()
{
    std::ifstream ifs(namesOfFiles::allAdminsFile, std::ios::binary);

    size_t numberOfAdmins = 0;
    ifs.read((char*)&numberOfAdmins, sizeof(size_t));

    for (size_t i = 0;i < numberOfAdmins;i++) {
        User* fromFile = new Admin();
        fromFile->readBinary(ifs);
        admins.push_back(fromFile);
    }
}

void stationsRepository::saveAllCardsIDs() const
{
    std::ofstream ofs(namesOfFiles::allIDcardsFile, std::ios::binary);

    size_t numberOfCards = discountCardIDs.getSize();
    ofs.write((const char*)&numberOfCards, sizeof(size_t));

    for (size_t i = 0;i < numberOfCards;i++) {
        unsigned int id = discountCardIDs[i];
        ofs.write((const char*)&id, sizeof(unsigned int));
    }
}

void stationsRepository::loadAllCardsIDs()
{
    std::ifstream ifs(namesOfFiles::allIDcardsFile, std::ios::binary);

    size_t numberOfCards = 0;
    ifs.read((char*)&numberOfCards, sizeof(size_t));

    discountCardIDs.clear();

    for (size_t i = 0;i < numberOfCards;i++) {
        unsigned int id;
        ifs.read((char*)&id, sizeof(unsigned int));
        discountCardIDs.push_back(id);
    }

    if (!numberOfCards) Utility::setlastCardID(100000);
    else
    {
        unsigned int lastID = getAllDiscountCardIDs()[numberOfCards - 1] + 1;
        Utility::setlastCardID(lastID);
    }

}

void stationsRepository::clearAllStaions()
{
    allStations.clear();
}

void stationsRepository::clearAllTrains()
{
    allTrains.clear();
}
