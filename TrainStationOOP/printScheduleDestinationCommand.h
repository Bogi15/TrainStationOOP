#pragma once
#include "Command.h"
class printScheduleDestinationCommand : public Command
{
public:
	printScheduleDestinationCommand(systemManager* manager);
	
	void execute()const override;
};

