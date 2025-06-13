#pragma once
#include "Command.h"
class printTrainCommand : public Command
{
public:
	printTrainCommand(systemManager* manager) : Command(manager){}

	void execute() const override;
};
