#pragma once
#include "Command.h"
class logoutCommand : public Command
{
public:
	logoutCommand(systemManager* manager):Command(manager){}

	void execute()const override;
};

