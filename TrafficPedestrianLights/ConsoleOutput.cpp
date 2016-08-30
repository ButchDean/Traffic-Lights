#include "ConsoleOutput.h"
#include "LightsTimer.h"
#include "LightsStatus.h"
#include <cassert>

#include <iostream>
using namespace std;

static HANDLE hConsole;

const char trafficLightFrame[] = "\n -   - \n|*| |D|\n -   - \n|*| |W|\n -   - \n|*|\n - \n";

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

    SetConsoleCursorPosition(hConsole, coordScreen );
}

static void ConfigureLightsAndDisplay(char* lights, int lightSet)
{
	for(unsigned int ch = 0; ch < strlen(trafficLightFrame); ch++)
	{
		switch(ch)
		{
		case 10:
			if(CLightsStatus::StatusDetail()->GetStatusRed(lightSet))
				SetConsoleTextAttribute(hConsole, RED);
			else
				SetConsoleTextAttribute(hConsole, NULL);
			break;
		case 14:
			if(CLightsStatus::StatusDetail()->GetStatusWalk(lightSet))
				SetConsoleTextAttribute(hConsole, NULL);
			else
				SetConsoleTextAttribute(hConsole, RED);
			break;
		case 26:
			if(CLightsStatus::StatusDetail()->GetStatusAmber(lightSet))
				SetConsoleTextAttribute(hConsole, AMBER);
			else
				SetConsoleTextAttribute(hConsole, NULL);
			break;
		case 30:
			if(CLightsStatus::StatusDetail()->GetStatusWalk(lightSet))
				SetConsoleTextAttribute(hConsole, GREEN);
			else
				SetConsoleTextAttribute(hConsole, NULL);
			break;
		case 42:
			if(CLightsStatus::StatusDetail()->GetStatusGreen(lightSet))
				SetConsoleTextAttribute(hConsole, GREEN);
			else
				SetConsoleTextAttribute(hConsole, NULL);
			break;
		default:
			SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE);
			break;
		}

		putchar(lights[ch]);
	}

}

void CConsoleOutput::UpdateDisplay(const int set)
{
	if(CLightsStatus::StatusDetail()->GetStatusGreen(set))
	{
		CLightsStatus::StatusDetail()->ClearStatusGreen(set);
		CLightsStatus::StatusDetail()->SetStatusAmber(set);

		CLightsStatus::StatusDetail()->ClearStatusWalk(set);
	}
	else
	if(CLightsStatus::StatusDetail()->GetStatusRed(set) && 
		CLightsStatus::StatusDetail()->GetStatusAmber(set))
	{
		CLightsStatus::StatusDetail()->ClearStatusRed(set);
		CLightsStatus::StatusDetail()->ClearStatusAmber(set);
		CLightsStatus::StatusDetail()->SetStatusGreen(set);

		CLightsStatus::StatusDetail()->ClearStatusWalk(set);
	}
	else
	if(CLightsStatus::StatusDetail()->GetStatusRed(set) && 
		!CLightsStatus::StatusDetail()->GetStatusAmber(set))
	{
		CLightsStatus::StatusDetail()->SetStatusAmber(set);

		CLightsStatus::StatusDetail()->ClearStatusWalk(set);
	}
	else
	if(CLightsStatus::StatusDetail()->GetStatusAmber(set))
	{
		CLightsStatus::StatusDetail()->ClearStatusAmber(set);
		CLightsStatus::StatusDetail()->SetStatusRed(set);

		CLightsStatus::StatusDetail()->SetStatusWalk(set);
	}
}

void CConsoleOutput::OutputDisplay()
{
	ClearScreen();

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	assert(hConsole != INVALID_HANDLE_VALUE || hConsole != NULL);

	SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE);

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