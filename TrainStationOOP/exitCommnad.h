#pragma once
#include "Command.h"

class exitCommnad : public Command
{
public:
	exitCommnad(systemManager* manager): Command(manager){}

	void execute()const override;
};

