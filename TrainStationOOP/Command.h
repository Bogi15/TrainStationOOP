#pragma once
#include "systemManager.h"

class Command
{
protected:
	systemManager* manager;

public:

	Command(systemManager* m);
	virtual void execute() const = 0;
	virtual ~Command() = default;

};

