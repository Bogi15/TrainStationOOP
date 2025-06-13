#pragma once
#pragma warning (disable: 4996)
#include <fstream>
#include <iostream>

namespace Constants
{
	constexpr size_t MAX_SIZE = 1024;
}

class String
{
private:
	char* data;
	size_t size;
	size_t capacity;

	explicit String(size_t newSize);

	unsigned int getNextPowerOfTwo(unsigned int n) const;
	unsigned int allocateCapacity(unsigned int size) const;
	unsigned int getLenOfNumber(unsigned int data) const;

	void resize(size_t newCapacity);

	void copyFrom(const String& other);
	void moveFrom(String&& other) noexcept;
	void free();

public:
	String();
	String(const char* data);
	String(unsigned int data);

	String(const String& other);
	String& operator=(const String& other);

	String(String&& other) noexcept;
	String& operator=(String&& other) noexcept;

	const char* c_str() const;


	size_t getSize() const;
	size_t getCapacity() const;

	const char& operator[](size_t idx) const;
	char& operator[](size_t idx);

	String& operator+=(const String& other);
	friend String operator+(const String& lhs, const String& rhs);

	String substr(size_t begin, size_t howMany) const;
	String trim()const;
	String stripSign() const;
	unsigned int getNumber() const;

	friend bool operator==(const String& lhs, const String& rhs);
	friend bool operator!=(const String& lhs, const String& rhs);

	friend bool operator<=(const String& lhs, const String& rhs);
	friend bool operator>=(const String& lhs, const String& rhs);

	friend bool operator<(const String& lhs, const String& rhs);
	friend bool operator>(const String& lhs, const String& rhs);

	friend std::istream& operator>>(std::istream& is, String& other);
	friend std::ostream& operator<<(std::ostream& os, const String& other);

	void writeBinary(std::ofstream& ofs) const;
	void readBinary(std::ifstream& ifs);

	~String();
};
