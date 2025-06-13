#pragma once
#include "Command.h"
class loginCommand : public Command
{
public:
	loginCommand(systemManager* manager) : Command(manager){}
	void execute()const override;
};

