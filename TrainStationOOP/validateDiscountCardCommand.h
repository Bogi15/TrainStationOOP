#pragma once
#include "Command.h"
class validateDiscountCardCommand : public Command
{
public: 
	validateDiscountCardCommand(systemManager* manager): Command(manager){}

	void execute()const override;
};

