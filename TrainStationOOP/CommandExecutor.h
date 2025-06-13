#pragma once
#include "Command.h"
#include "CommandFactory.h"

class CommandExecutor
{
	systemManager* manager = nullptr;

public:
	CommandExecutor(systemManager* m);

	void executeCommand();
	
};

