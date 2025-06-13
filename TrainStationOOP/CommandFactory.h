#pragma once
#include "Command.h"
#include "systemManager.h"

#include "printStationsCommand.h"
#include "printSchedule.h"
#include "printScheduleDestinationCommand.h"
#include "printScheduleTimeCommand.h"
#include "printTrainCommand.h"
#include "printTrainWagonCommand.h"


#include "loginCommand.h"
#include "logoutCommand.h"
#include "addStationCommand.h"
#include "addTrainCommand.h"


Command* createCommand(const String& command, systemManager* s);
