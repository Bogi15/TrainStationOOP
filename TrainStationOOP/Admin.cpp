#include "Admin.h"

bool Admin::isAdmin() const
{
    return true;
}

void Admin::writeBinary(std::ofstream& ofs) const
{
    name.writeBinary(ofs);
    password.writeBinary(ofs);
}

void Admin::readBinary(std::ifstream& ifs)
{
    name.readBinary(ifs);
    password.readBinary(ifs);
}

const String& Admin::getName() const
{
    return name;
}

bool Admin::validatePassword(const String& p) const
{
    return password == p;
}
