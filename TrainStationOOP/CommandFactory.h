#pragma once
#include "Command.h"
#include "systemManager.h"

#include "printStationsCommand.h"
#include "printSchedule.h"
#include "printScheduleDestinationCommand.h"
#include "printScheduleTimeCommand.h"
#include "printTrainCommand.h"
#include "printTrainWagonCommand.h"
#include "buyTicketCommand.h"
#include "buyTicketDIscountCommand.h"

#include "loginCommand.h"
#include "logoutCommand.h"
#include "addStationCommand.h"
#include "addTrainCommand.h"
#include "removeTrainCommand.h"
#include "createDiscountCardCommand.h"
#include "validateDiscountCardCommand.h"
#include "addWagonCommand.h"


Command* createCommand(const String& command, systemManager* s);
