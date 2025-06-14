#pragma once
#include "Command.h"
class removeTrainCommand : public Command
{
public:
	removeTrainCommand(systemManager* manager):Command(manager){}

	void execute()const override;
};

