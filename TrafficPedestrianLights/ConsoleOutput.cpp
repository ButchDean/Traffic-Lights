#include <cstdio>
#include <cmath>

#include "ConsoleOutput.h"
#include "LightsStatus.h"
#include "CountdownTimer.h"

HANDLE hConsole;

namespace Console
{
	void CConsoleOutput::_UpdateCountdownTimer()
	{
		remainingSecs = GetCountdownUpperBound();
		char strCountdown[3] = {0};

		if (remainingSecs > 99)
		{
			std::perror("C'mon man! Nobody is going to wait for more than 1 minute 39 seconds!");

			return;
		}

		if (UpdateCountdown())
			remainingSecs--;

		// Get most significant digit
		strCountdown[0] = 0x30 + static_cast<int>(std::ceil(remainingSecs / 10));

		// Get least significant digit
		strCountdown[1] = 0x30 + static_cast<int>((remainingSecs - std::ceil(remainingSecs / 10) * 10));

		countdown = std::string(strCountdown);
	}

	static void ClearScreen()
	{
		COORD coordScreen = {0, 0};

		DWORD cCharsWritten;
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		DWORD conSize;

		SetConsoleTextAttribute(hConsole, 0);

		GetConsoleScreenBufferInfo(hConsole, &csbi);
		conSize = csbi.dwSize.X * csbi.dwSize.Y;

		FillConsoleOutputCharacter(hConsole, ' ',
			conSize, coordScreen, &cCharsWritten);

		GetConsoleScreenBufferInfo(hConsole, &csbi);

		FillConsoleOutputAttribute(hConsole, csbi.wAttributes,
			conSize, coordScreen, &cCharsWritten);

		SetConsoleCursorPosition(hConsole, coordScreen);
	}

	void CConsoleOutput::ConfigureLightsAndDisplay(char* lights, int lightSet)
	{
		for (unsigned int ch = 0; ch < trafficLightFrame.size(); ch++)
		{
			switch (ch)
			{
				// Main signals
				case 6:
					if (localStatus->GetStatusRed(lightSet))
						SetConsoleTextAttribute(hConsole, RED);
					else
						SetConsoleTextAttribute(hConsole, NULL);
					break;
				case 19:
					if (localStatus->GetStatusAmber(lightSet))
						SetConsoleTextAttribute(hConsole, AMBER);
					else
						SetConsoleTextAttribute(hConsole, NULL);
					break;
				case 37:
					if (localStatus->GetStatusGreen(lightSet))
						SetConsoleTextAttribute(hConsole, GREEN);
					else
						SetConsoleTextAttribute(hConsole, NULL);
					break;

				// Pedestrian signals
				case 23:
					if (localStatus->GetStatusWalk(lightSet))
						SetConsoleTextAttribute(hConsole, NULL);
					else
						SetConsoleTextAttribute(hConsole, RED);
					break;
				case 24:
					if (localStatus->GetStatusWalk(lightSet))
						SetConsoleTextAttribute(hConsole, NULL);
					else
						SetConsoleTextAttribute(hConsole, RED);
					break;
				case 41:
					if (localStatus->GetStatusWalk(lightSet))
						SetConsoleTextAttribute(hConsole, GREEN);
					else
						SetConsoleTextAttribute(hConsole, NULL);
					break;
				case 42:
					if (localStatus->GetStatusWalk(lightSet))
						SetConsoleTextAttribute(hConsole, GREEN);
					else
						SetConsoleTextAttribute(hConsole, NULL);
					break;

				// Signal frame
				default:
					SetConsoleTextAttribute(hConsole, AMBER_BACKGROUND);
					break;
			}

			putchar(lights[ch]);
		}

	}

	void CConsoleOutput::UpdateDisplay(const int set)
	{
		if(localStatus->GetStatusGreen(set))
		{
			localStatus->ClearStatusGreen(set);
			localStatus->SetStatusAmber(set);
			localStatus->ClearStatusRed(set);

			localStatus->ClearStatusWalk(set);
		}
		else
		if(localStatus->GetStatusAmber(set))
		{
			localStatus->ClearStatusGreen(set);
			localStatus->ClearStatusAmber(set);
			localStatus->SetStatusRed(set);

			localStatus->SetStatusWalk(set);
		}
		else
		if(localStatus->GetStatusRed(set))
		{
			localStatus->SetStatusGreen(set);
			localStatus->ClearStatusAmber(set);
			localStatus->ClearStatusRed(set);

			localStatus->ClearStatusWalk(set);
		}
	}

	void CConsoleOutput::OutputDisplay()
	{
		ClearScreen();

		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		assert(hConsole != INVALID_HANDLE_VALUE || hConsole != NULL);

		_UpdateCountdownTimer();

		trafficLightFrame = SIGFRAMEPT1 + countdown + SIGFRAMEPT2;

		// Render top set of signals.
		ConfigureLightsAndDisplay((char*)trafficLightFrame.c_str(), 0);

		// Render bottom set of signals.
		ConfigureLightsAndDisplay((char*)trafficLightFrame.c_str(), 1);
	}
}