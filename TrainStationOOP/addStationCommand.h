#pragma once
#include "Command.h"
class addStationCommand : public Command
{
public:
	addStationCommand(systemManager* manager):Command(manager){}

	void execute()const override;
};

