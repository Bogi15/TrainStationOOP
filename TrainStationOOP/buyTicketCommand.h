#pragma once
#include "Command.h"
class buyTicketCommand : public Command
{
public:
	buyTicketCommand(systemManager* manager):Command(manager){}

	void execute()const override;
};

