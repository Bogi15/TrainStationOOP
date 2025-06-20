#include "String.h"

String::String() : String("")
{
}

String::String(const char* data) : size(strlen(data)), capacity(allocateCapacity(size))
{
	this->data = new char[this->capacity];
	strcpy(this->data, data);
}

String::String(unsigned int data)
{
	if (data == 0) {
		size = 1;
		capacity = 2;
		this->data = new char[capacity];
		this->data[0] = '0';
		this->data[1] = '\0';
		return;
	}

	size_t len = getLenOfNumber(data);
	size = len;
	capacity = len + 1;
	this->data = new char[capacity];
	size_t index = len - 1;

	while (data) {
		this->data[index] = '0' + data % 10;
		data /= 10;
		index--;
	}

	this->data[len] = '\0';
}

String::String(size_t newSize) : size(0)
{
	this->capacity = allocateCapacity(newSize);
	this->data = new char[this->capacity] { '\0' };
}

String::String(const String& other)
{
	copyFrom(other);
}

String& String::operator=(const String& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

String::String(String&& other) noexcept
{
	moveFrom(std::move(other));
}

String& String::operator=(String&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

const char* String::c_str() const
{
	return this->data;
}

size_t String::getSize() const
{
	return this->size;
}

size_t String::getCapacity() const
{
	return this->capacity;
}

const char& String::operator[](size_t idx) const
{
	return this->data[idx];
}

char& String::operator[](size_t idx)
{
	if (idx >= size) throw std::out_of_range("Index out of bounds");
	return this->data[idx];
}

String& String::operator+=(const String& other)
{
	if (getSize() + other.getSize() >= getCapacity())
	{
		resize(allocateCapacity(getSize() + other.getSize()));
	}

	strncat(this->data, other.data, other.getSize());

	this->size += other.getSize();

	return *this;
}

String operator+(const String& lhs, const String& rhs)
{
	String toReturn(lhs.getSize() + rhs.getSize());

	toReturn += lhs;
	toReturn += rhs;

	return toReturn;
}

String String::substr(size_t begin, size_t howMany) const
{
	if (begin + howMany > getSize()) return String("");

	String toReturn(howMany);
	strncat(toReturn.data, this->data + begin, howMany);
	return toReturn;
}

String String::trim() const
{
	if (!data || getSize() == 0) {
		return String("");
	}
	size_t start = 0;
	size_t finish = getSize();

	while (start < finish && data[start] == ' ') {
		start++;
	}

	while (start < finish && data[finish - 1] == ' ') {
		finish--;
	}

	return substr(start, finish - start);
}

String String::stripSign() const
{
	if (getSize() > 0 && data[0] == '|') {
		return substr(1, getSize() - 1); 
	}
	return *this;
}

bool operator==(const String& lhs, const String& rhs)
{
	return strcmp(lhs.data, rhs.data) == 0;
}

bool operator!=(const String& lhs, const String& rhs)
{
	return strcmp(lhs.data, rhs.data) != 0;
}

bool operator<=(const String& lhs, const String& rhs)
{
	return strcmp(lhs.data, rhs.data) <= 0;
}

bool operator>=(const String& lhs, const String& rhs)
{
	return strcmp(lhs.data, rhs.data) >= 0;
}

bool operator<(const String& lhs, const String& rhs)
{
	return strcmp(lhs.data, rhs.data) < 0;
}

bool operator>(const String& lhs, const String& rhs)
{
	return strcmp(lhs.data, rhs.data) > 0;
}

std::istream& operator>>(std::istream& is, String& other)
{
	char buff[Constants::MAX_SIZE + 1];
	is >> buff;

	size_t buffLength = strlen(buff);

	if (buffLength >= other.getCapacity())
	{
		other.resize(other.allocateCapacity(buffLength));
	}

	strcpy(other.data, buff);

	other.size = buffLength;

	return is;
}

std::ostream& operator<<(std::ostream& os, const String& other)
{
	return os << other.data;
}

void String::writeBinary(std::ofstream& ofs) const
{
	ofs.write((const char*)&this->size, sizeof(size_t));
	ofs.write(this->data, this->size);
}

void String::readBinary(std::ifstream& ifs)
{
	free();

	size_t newSize = 0;
	ifs.read((char*)&newSize, sizeof(size_t));
	unsigned int cap = allocateCapacity(newSize);

	this->capacity = cap;
	this->data = new char[cap];
	if (newSize > 0) {
		ifs.read(this->data, newSize);
	}

	this->data[newSize] = '\0';
	this->size = newSize;
}

bool String::findSubStr(const String& s) const
{
	size_t n = this->size;
	size_t m = s.getSize();

	if (m == 0) return true;
	if (m > n) return false;
	

	for (size_t i = 0;i + m <= n;i++) {
		bool match = true;
		for (size_t j = 0;j < m;j++) {
			if (data[i + j] != s.data[j]) {
				match = false;
				continue;
			}
		}
		if (match) return true;
	}

	return false;
}

String::~String()
{
	free();
}

unsigned int String::getNextPowerOfTwo(unsigned int n) const
{
	if (n == 0) return 1;

	while (n & (n - 1))
	{
		n &= (n - 1);
	}

	return n << 1;
}

unsigned int String::allocateCapacity(unsigned int size) const
{
	return std::max(getNextPowerOfTwo(size + 1), 8u);
}

unsigned int String::getLenOfNumber(unsigned int data) const
{
	unsigned int len = 0;
	while (data) {
		data /= 10;
		len++;
	}

	return len;
}

unsigned int String::getNumber() const
{
	if (!data || getSize() == 0) {
		return 0;
	}
	unsigned int number = 0;
	bool foundDigit = false;

	for (size_t i = 0; i < getSize(); ++i) {
		char ch = data[i];
		if (ch >= '0' && ch <= '9') {
			foundDigit = true;
			number = number * 10 + (ch - '0');
		}
		else if (foundDigit) {
			break;
		}
	}

	return number;
}

void String::resize(size_t newCapacity)
{
	this->capacity = newCapacity;

	char* newData = new char[this->capacity];
	strcpy(newData, this->data);

	delete[] this->data;
	this->data = newData;
}

void String::copyFrom(const String& other)
{
	this->size = other.size;
	this->capacity = other.capacity;

	this->data = new char[strlen(other.data) + 1];
	strcpy(this->data, other.data);
}

void String::moveFrom(String&& other) noexcept
{
	this->data = other.data;
	this->size = other.size;
	this->capacity = other.capacity;

	other.data = nullptr;
	other.size = other.capacity = 0;
}

void String::free()
{
	delete[] this->data;

	this->data = nullptr;
	this->size = this->capacity = 0;
}
