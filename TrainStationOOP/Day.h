#pragma once
class Day
{
private:

	size_t day;
	size_t month;
	size_t year;

public:

	Day(size_t day, size_t month, size_t year);

	size_t getDay() const;
	size_t getMonth() const;
	size_t getYear() const;

	void setDay(size_t day);
	void setMonth(size_t month);
	void setYear(size_t year);

};

