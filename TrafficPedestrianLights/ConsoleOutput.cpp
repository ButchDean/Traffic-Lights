#include "ConsoleOutput.h"
#include "LightsTimer.h"
#include "LightsStatus.h"
#include <cstring>

#include <iostream>
using namespace std;

HANDLE hConsole;

static string countdown = "WK";

static string trafficLightFrame = "\n - \n|@|\n -   -- \n|@| |DW|\n -   -- \n|@| |" + countdown + "|\n -   -- \n";

namespace Console
{
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

	static void ConfigureLightsAndDisplay(char* lights, int lightSet)
	{
		for (unsigned int ch = 0; ch < trafficLightFrame.size(); ch++)
		{
			switch (ch)
			{
				// Main signals
				case 6:
					if (Signals::CLightsStatus::StatusDetail()->GetStatusRed(lightSet))
						SetConsoleTextAttribute(hConsole, RED);
					else
						SetConsoleTextAttribute(hConsole, NULL);
					break;
				case 19:
					if (Signals::CLightsStatus::StatusDetail()->GetStatusAmber(lightSet))
						SetConsoleTextAttribute(hConsole, AMBER);
					else
						SetConsoleTextAttribute(hConsole, NULL);
					break;
				case 37:
					if (Signals::CLightsStatus::StatusDetail()->GetStatusGreen(lightSet))
						SetConsoleTextAttribute(hConsole, GREEN);
					else
						SetConsoleTextAttribute(hConsole, NULL);
					break;

				// Pedestrian signals
				case 23:
					if (Signals::CLightsStatus::StatusDetail()->GetStatusWalk(lightSet))
						SetConsoleTextAttribute(hConsole, NULL);
					else
						SetConsoleTextAttribute(hConsole, RED);
					break;
				case 24:
					if (Signals::CLightsStatus::StatusDetail()->GetStatusWalk(lightSet))
						SetConsoleTextAttribute(hConsole, NULL);
					else
						SetConsoleTextAttribute(hConsole, RED);
					break;
				case 41:
					if (Signals::CLightsStatus::StatusDetail()->GetStatusWalk(lightSet))
						SetConsoleTextAttribute(hConsole, GREEN);
					else
						SetConsoleTextAttribute(hConsole, NULL);
					break;
				case 42:
					if (Signals::CLightsStatus::StatusDetail()->GetStatusWalk(lightSet))
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
		if(Signals::CLightsStatus::StatusDetail()->GetStatusGreen(set))
		{
			Signals::CLightsStatus::StatusDetail()->ClearStatusGreen(set);
			Signals::CLightsStatus::StatusDetail()->SetStatusAmber(set);
			Signals::CLightsStatus::StatusDetail()->ClearStatusRed(set);

			Signals::CLightsStatus::StatusDetail()->ClearStatusWalk(set);
		}
		else
		if(Signals::CLightsStatus::StatusDetail()->GetStatusAmber(set))
		{
			Signals::CLightsStatus::StatusDetail()->ClearStatusGreen(set);
			Signals::CLightsStatus::StatusDetail()->ClearStatusAmber(set);
			Signals::CLightsStatus::StatusDetail()->SetStatusRed(set);

			Signals::CLightsStatus::StatusDetail()->SetStatusWalk(set);
		}
		else
		if(Signals::CLightsStatus::StatusDetail()->GetStatusRed(set))
		{
			Signals::CLightsStatus::StatusDetail()->SetStatusGreen(set);
			Signals::CLightsStatus::StatusDetail()->ClearStatusAmber(set);
			Signals::CLightsStatus::StatusDetail()->ClearStatusRed(set);

			Signals::CLightsStatus::StatusDetail()->ClearStatusWalk(set);
		}
	}

	void CConsoleOutput::OutputDisplay()
	{
		ClearScreen();

		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		assert(hConsole != INVALID_HANDLE_VALUE || hConsole != NULL);

		// Render top set of signals.
		ConfigureLightsAndDisplay((char*)trafficLightFrame.c_str(), 0);

		// Render bottom set of signals.
		ConfigureLightsAndDisplay((char*)trafficLightFrame.c_str(), 1);
	}
}