#pragma once
#include "Command.h"
class addTrainCommand : public Command
{
public:
	addTrainCommand(systemManager* manager): Command(manager){}

	void execute()const override;
};

