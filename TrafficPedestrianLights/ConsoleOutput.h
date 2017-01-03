#ifndef _CONSOLE_OUTPUT_
#define _CONSOLE_OUTPUT_

#include <windows.h>
#include <cassert>
#include <memory>
#include <string>
#include "LightsStatus.h"
#include "CountdownTimer.h"

#define RED		FOREGROUND_RED | FOREGROUND_INTENSITY
#define AMBER	FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define GREEN	FOREGROUND_GREEN | FOREGROUND_INTENSITY

#define AMBER_BACKGROUND BACKGROUND_RED | BACKGROUND_GREEN

namespace Console
{
	class CConsoleOutput : public CountdownTimer::CTimer
	{
	public:

		CConsoleOutput(std::shared_ptr<Signals::CLightsStatus> ls)
		{
			localStatus = ls;

			countdown = "WK";
			trafficLightFrame = SIGFRAMEPT1 + countdown + SIGFRAMEPT2;
		}
		~CConsoleOutput() {}

		void ConfigureLightsAndDisplay(char* lights, int lightSet);
		void UpdateDisplay(const int set);
		void OutputDisplay();

	private:

		std::string countdown;
		std::string trafficLightFrame;

		std::shared_ptr<Signals::CLightsStatus> localStatus;
		std::shared_ptr<CountdownTimer::CTimer> localTimer;

		const std::string SIGFRAMEPT1 = "\n - \n|@|\n -   -- \n|@| |DW|\n -   -- \n|@| |";
		const std::string SIGFRAMEPT2 = "|\n -   -- \n";

		void _UpdateCountDownTimer();
	};
}
#endif