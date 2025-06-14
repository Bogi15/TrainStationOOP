#pragma once
#include "Command.h"
class buyTicketDIscountCommand : public Command
{
public:
	buyTicketDIscountCommand(systemManager* manager):Command(manager){}

	void execute()const override;
};

