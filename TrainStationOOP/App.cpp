#include "App.h"

void App::run()
{
	systemManager manager;
	CommandExecutor ce(&manager);
	ce.executeCommand();
}
