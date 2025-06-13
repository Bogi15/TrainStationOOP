#pragma once
#include "Command.h"
class printStationsCommand : public Command
{
public:

	printStationsCommand(systemManager* manager);
	void execute()const override;
};

