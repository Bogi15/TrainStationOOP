#pragma once
#include "User.h"
class OrdinaryUser : public User
{
public:
	OrdinaryUser() = default;

	void writeBinary(std::ofstream& ofs) const override;
	void readBinary(std::ifstream& ifs) override;
};

