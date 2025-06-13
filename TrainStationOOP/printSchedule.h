#pragma once
#include "Command.h"
class printSchedule : public Command
{
public:
	printSchedule(systemManager* manager);
	void execute()const override;
};

