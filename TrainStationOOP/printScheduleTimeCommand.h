#pragma once
#include "Command.h"
class printScheduleTimeCommand : public Command
{
public:
	printScheduleTimeCommand(systemManager* manager):Command(manager){}

	void execute()const override;
};

