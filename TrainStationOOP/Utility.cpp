#include "Utility.h"
#include <sstream>
#include <iomanip>
#include <ctime>

#include "DiscountCard.h"
#include "DiscountCardAge.h"
#include "DiscountCardDistance.h"
#include "DiscountCardRoute.h"

void Utility::fillWithDashSign(size_t len)
{
    while (len--) {
        std::cout << "-";
    }
    std::cout << std::endl;
}

String Utility::fillWithSign(size_t len) const
{
    len /= 2;
    String toReturn("");
    while (len--) {
        toReturn += "=";
    }

    return toReturn;
}

String Utility::fillWithSpaces(size_t len) const
{

    String toReturn("");
    while (len--) {
        toReturn += " ";
    }

    return toReturn;
}

size_t Utility::calculateFilling(const String& str) const
{
    return ConstantsU::MAX_LINE_LEN - str.getSize();
}

void Utility::failMessage()
{
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::invalid_argument("wrong type of data given");
    }
}

std::tm Utility::parseDateTime(const String& s)
{
    int d, m, Y, H, M;

    std::sscanf(s.c_str(), "%d/%d/%d %d:%d", &d, &m, &Y, &H, &M);

    std::tm tm{};
    tm.tm_sec = 0;
    tm.tm_min = M;
    tm.tm_hour = H;
    tm.tm_mday = d;
    tm.tm_mon = m - 1;      
    tm.tm_year = Y - 1900;    
    tm.tm_isdst = -1;        

    return tm;
}

std::time_t Utility::toTimeT(const std::tm& tm)
{
    return std::mktime(const_cast<std::tm*>(&tm));
}

BaseVagon* Utility::create(VagonType tag)
{

    switch (tag) {
        case VagonType::firstClass: return new FirstClassVagon();
        case VagonType::secondClass: return new SecondClassVagon();
        case VagonType::sleeping: return new SleepingVagon();
        default: 
            throw std::runtime_error("Unknown VagonType");
    }
}

BaseVagon* Utility::readFromStream(std::ifstream& ifs)
{
    VagonType tag;
    ifs.read((char*)&tag, sizeof(tag));
    if (!ifs.good()) {
        throw std::runtime_error("VagonFactory: cannot read tag");
    }

    BaseVagon* v = create(tag);
    v->readVagonBinary(ifs);
    return v;

}

BaseVagon* Utility::createWithString(const String& s)
{
    if (s == "first-class") {
        unsigned int basePrice;
        std::cin >> basePrice;
        failMessage();

        double comfortFactor;
        std::cin >> comfortFactor;
        failMessage();
       
        if (comfortFactor < 0 || comfortFactor > 1) throw std::invalid_argument("The comfort factor is between 0 and 1!");

        return new FirstClassVagon(basePrice, comfortFactor);

    }
    else if (s == "second-class") {
        unsigned int basePrice;
        std::cin >> basePrice;
        failMessage();

        unsigned int kgPrice;
        std::cin >> kgPrice;
        failMessage();

        return new SecondClassVagon(basePrice,kgPrice);
    }
    else if (s == "sleeping-wagon") {
        unsigned int basePrice;
        std::cin >> basePrice;
        failMessage();

        unsigned int hunderedKilimetersPrice;
        std::cin >> hunderedKilimetersPrice;
        failMessage();

        return new SleepingVagon(basePrice,hunderedKilimetersPrice);
    }  
    else
        return nullptr;
}

bool Utility::isValidDate(const String& date)
{
    if (date.getSize() != 10 || date[2] != '/' || date[5] != '/')
        return false;

    int d, m, y;
    char extra;
    int fields = std::sscanf(date.c_str(), "%2d/%2d/%4d%c", &d, &m, &y, &extra);
    if (fields != 3) 
        return false;

    if (y < 1900 || m < 1 || m > 12 || d < 1)
        return false;

    static int dim[13] =
    { 0, 31,28,31,30,31,30,31,31,30,31,30,31 };

    bool isLeap = (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0));
    if (isLeap) dim[2] = 29;
    else         dim[2] = 28;

    if (d > dim[m])
        return false;

    return true;
}

bool Utility::isValidHour(const String& time)
{
    if (time.getSize() != 5 || time[2] != ':') return false;

    int hour = (time[0] - '0') * 10 + (time[1] - '0');
    int minute = (time[3] - '0') * 10 + (time[4] - '0');

    if (hour < 0 || hour > 23) return false;
    if (minute < 0 || minute > 59) return false;

    return true;

    
}

bool Utility::isTimeToFree(const String& t)
{
    std::tm tm{};
    std::istringstream ss(t.c_str());
    ss >> std::get_time(&tm, "%d/%m/%Y %H:%M");
    if (ss.fail()) {
        throw std::runtime_error("Failed to parse time string: " + std::string(t.c_str()));
    }
    tm.tm_sec = 0;
    tm.tm_isdst = -1;

    std::time_t given = std::mktime(&tm);

    std::time_t now = std::time(nullptr);
    constexpr int THIRTY_MINUTES = 30 * 60;

    return now >= (given + THIRTY_MINUTES);
}

bool Utility::hasDeparted(const String& t)
{
    std::tm tm = Utility::parseDateTime(t);

    std::time_t event_t = Utility::toTimeT(tm);

    return std::time(nullptr) >= event_t;
    
}

DiscountCard* Utility::createDiscountCard(const String& type)
{
    if (type == "route-card")
        return new DiscountCardRoute();
    else if (type == "age-card")
        return new DiscountCardAge();
    else if (type == "distance-card")
        return new DiscountCardDistance();
}

DiscountCard* Utility::createDiscountCardFromFirstChar(const String& type)
{
    if (type.findSubStr("RouteCard_"))
        return new DiscountCardRoute();
    else if (type.findSubStr("AgeCard_"))
        return new DiscountCardAge();
    else if (type.findSubStr("DistanceCard_"))
        return new DiscountCardDistance();
    else return nullptr;
}

void Utility::setlastCardID(unsigned int ID)
{
    DiscountCard::setNextID(ID);
}
