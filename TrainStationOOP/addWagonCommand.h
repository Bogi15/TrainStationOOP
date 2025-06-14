#pragma once
#include "Command.h"
class addWagonCommand : public Command
{
public:
	addWagonCommand(systemManager* manager):Command(manager){}

	void execute()const override;
};

