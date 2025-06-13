#pragma once
#include "Command.h"
class printTrainWagonCommand : public Command
{
public:
	printTrainWagonCommand(systemManager* manager):Command(manager){}

	void execute()const override;
};

