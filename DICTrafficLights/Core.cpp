#include <windows.h>
#include <iostream>
using namespace std;

#include "ConsoleOutput.h"
#include "LightsStatus.h"
#include "LightsTimer.h"

#define LIGHTSTATUS		CLightsStatus::StatusDetail()
#define LIGHTSDISPLAY	CConsoleOutput::ConsoleInst()

int main()
{
	// implement: Initialize state.

	int lightsSet = 0;

	while(!(GetKeyState(VK_ESCAPE) & 0x80))
	{
		if(TimeElapsed(2))
		{
			LIGHTSDISPLAY->UpdateDisplay(lightsSet);
			LIGHTSDISPLAY->OutputDisplay();

			// Complete implementation.
	
		}

	}

	return 0;
}