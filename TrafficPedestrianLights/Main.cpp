#include <windows.h>
#include <memory>

#include "ConsoleOutput.h"
#include "LightsStatus.h"
#include "LightsTimer.h"
#include "CountdownTimer.h"

#define LIGHTSTATUS		Signals::CLightsStatus::StatusDetail()
#define LIGHTSDISPLAY	Console::CConsoleOutput::ConsoleInst()

extern HANDLE hConsole;

int main()
{
	// Initialize state.
	if(LIGHTSTATUS->SystemIsReset())
	{
		LIGHTSTATUS->SetStatusRed(1);
		LIGHTSTATUS->SetStatusAmber(0);

		LIGHTSTATUS->SetStatusWalk(0);
		LIGHTSTATUS->SetStatusWalk(1);

		LIGHTSDISPLAY->OutputDisplay();
	}

	int lightsSet = 0;

	// Init countdown timer.
	std::unique_ptr<CountdownTimer::CTimer> countdown(new CountdownTimer::CTimer(10));

	while(!(GetKeyState(VK_ESCAPE) & 0x80))
	{
		if(TimeElapsed(2))
		{
			LIGHTSDISPLAY->UpdateDisplay(lightsSet);
			LIGHTSDISPLAY->OutputDisplay();

			lightsSet = LIGHTSTATUS->CycleLights(lightsSet);
		}

	}

	SetConsoleTextAttribute(hConsole, RED);

	return 0;
}