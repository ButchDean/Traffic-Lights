#include <windows.h>
#include <memory>

#include "ConsoleOutput.h"
#include "LightsStatus.h"
#include "CountdownTimer.h"

extern HANDLE hConsole;

int main()
{
	std::shared_ptr<Signals::CLightsStatus> signal(new Signals::CLightsStatus);
	std::unique_ptr<Console::CConsoleOutput> consoleOut(new Console::CConsoleOutput(signal));
	
	// Init countdown timer.
	std::unique_ptr<CountdownTimer::CTimer> countdown(new CountdownTimer::CTimer(10));
	int lightsSet = 0;

	// Initialize state.
	if(signal->SystemIsReset())
	{
		signal->SetStatusRed(1);
		signal->SetStatusAmber(0);

		signal->SetStatusWalk(0);
		signal->SetStatusWalk(1);

		consoleOut->OutputDisplay();
	}

	while(!(GetKeyState(VK_ESCAPE) & 0x80))
	{
		if(countdown->UpdateSequence())
		{
			consoleOut->UpdateDisplay(lightsSet);
			consoleOut->OutputDisplay();

			lightsSet = signal->CycleLights(lightsSet);
		}

	}

	SetConsoleTextAttribute(hConsole, RED);

	return 0;
}