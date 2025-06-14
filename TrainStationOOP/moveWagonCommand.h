#pragma once
#include "Command.h"
class moveWagonCommand : public Command
{
public:
	moveWagonCommand(systemManager* manager):Command(manager){}

	void execute()const override;
};

