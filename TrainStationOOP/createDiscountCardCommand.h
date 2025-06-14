#pragma once
#include "Command.h"
class createDiscountCardCommand : public Command
{
public:
	createDiscountCardCommand(systemManager* manager):Command(manager){}

	void execute()const override;
};

