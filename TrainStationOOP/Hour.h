#pragma once
class Hour
{
private:
	size_t hour;
	size_t minute;

public:

	Hour(size_t hour, size_t minute);
	size_t getHour() const;
	size_t getMinute() const;

	void setHour(size_t hour);
	void setMinute(size_t minute);

};

