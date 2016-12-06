#include "ConsoleOutput.h"
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

		// Render top set of signals.
		ConfigureLightsAndDisplay((char*)trafficLightFrame.c_str(), 0);

		// Render bottom set of signals.
		ConfigureLightsAndDisplay((char*)trafficLightFrame.c_str(), 1);
	}
}