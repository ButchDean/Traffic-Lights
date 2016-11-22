#include "ConsoleOutput.h"
#include "LightsTimer.h"
#include "LightsStatus.h"
#include <cassert>

#include <iostream>
using namespace std;

HANDLE hConsole;

const char trafficLightFrame[] = "\n - \n|@|\n -   - \n|@| |D|\n -   - \n|@| |W|\n -   - \n";

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
		for (unsigned int ch = 0; ch < strlen(trafficLightFrame); ch++)
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
				case 18:
					if (Signals::CLightsStatus::StatusDetail()->GetStatusAmber(lightSet))
						SetConsoleTextAttribute(hConsole, AMBER);
					else
						SetConsoleTextAttribute(hConsole, NULL);
					break;
				case 34:
					if (Signals::CLightsStatus::StatusDetail()->GetStatusGreen(lightSet))
						SetConsoleTextAttribute(hConsole, GREEN);
					else
						SetConsoleTextAttribute(hConsole, NULL);
					break;

				// Pedestrian signals
				case 22:
					if (Signals::CLightsStatus::StatusDetail()->GetStatusWalk(lightSet))
						SetConsoleTextAttribute(hConsole, NULL);
					else
						SetConsoleTextAttribute(hConsole, RED);
					break;
				case 38:
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
		if (Signals::CLightsStatus::StatusDetail()->GetStatusGreen(set))
		{
			Signals::CLightsStatus::StatusDetail()->ClearStatusGreen(set);
			Signals::CLightsStatus::StatusDetail()->SetStatusAmber(set);

			Signals::CLightsStatus::StatusDetail()->ClearStatusWalk(set);
		}
		else
			if (Signals::CLightsStatus::StatusDetail()->GetStatusRed(set) &&
				Signals::CLightsStatus::StatusDetail()->GetStatusAmber(set))
			{
				Signals::CLightsStatus::StatusDetail()->ClearStatusRed(set);
				Signals::CLightsStatus::StatusDetail()->ClearStatusAmber(set);
				Signals::CLightsStatus::StatusDetail()->SetStatusGreen(set);

				Signals::CLightsStatus::StatusDetail()->ClearStatusWalk(set);
			}
			else
				if (Signals::CLightsStatus::StatusDetail()->GetStatusRed(set) &&
					!Signals::CLightsStatus::StatusDetail()->GetStatusAmber(set))
				{
					Signals::CLightsStatus::StatusDetail()->SetStatusAmber(set);

					Signals::CLightsStatus::StatusDetail()->ClearStatusWalk(set);
				}
				else
					if (Signals::CLightsStatus::StatusDetail()->GetStatusAmber(set))
					{
						Signals::CLightsStatus::StatusDetail()->ClearStatusAmber(set);
						Signals::CLightsStatus::StatusDetail()->SetStatusRed(set);

						Signals::CLightsStatus::StatusDetail()->SetStatusWalk(set);
					}
	}

	void CConsoleOutput::OutputDisplay()
	{
		ClearScreen();

		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		assert(hConsole != INVALID_HANDLE_VALUE || hConsole != NULL);

		char lightsBuf[MAXBUF] = {0};

		{
			strcpy((char*)&lightsBuf, (char*)&trafficLightFrame);
			ConfigureLightsAndDisplay(lightsBuf, 0);
		}

		{
			strcpy((char*)&lightsBuf, (char*)&trafficLightFrame);
			ConfigureLightsAndDisplay(lightsBuf, 1);
		}
	}
}