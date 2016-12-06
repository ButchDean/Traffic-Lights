#ifndef _CONSOLE_OUTPUT_
#define _CONSOLE_OUTPUT_

#include <windows.h>
#include <stdio.h>
#include <cassert>
#include <memory>
#include "LightsStatus.h"

#define RED		FOREGROUND_RED | FOREGROUND_INTENSITY
#define AMBER	FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define GREEN	FOREGROUND_GREEN | FOREGROUND_INTENSITY

#define AMBER_BACKGROUND BACKGROUND_RED | BACKGROUND_GREEN

namespace Console
{
	class CConsoleOutput
	{
	public:

		CConsoleOutput(std::shared_ptr<Signals::CLightsStatus> ls) 
		{
			localStatus = ls;
		}
		~CConsoleOutput() {}

		void ConfigureLightsAndDisplay(char* lights, int lightSet);

		void UpdateDisplay(const int set);
		void OutputDisplay();

	private:

		std::shared_ptr<Signals::CLightsStatus> localStatus;

	};
}
#endif