#include "ConsoleOutput.h"
#include "LightsTimer.h"
#include "LightsStatus.h"
#include <cassert>

#include <iostream>
using namespace std;

static HANDLE hConsole;

const char trafficLightFrame[] = "\n - \n|*|\n - \n - \n";

static void ClearScreen()
{
    COORD coordScreen = {0, 0};    

    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi; 
    DWORD conSize;                 
	
	SetConsoleTextAtribute(hConsole, 0);

    GetConsoleScreenBufferInfo(hConsole, &csbi);
    conSize = csbi.dwSize.X * csbi.dwSize.Y;

    FillConsoleOutputCharacter(hConsole, ' ',
       conSize, coordScreen, &cCharsWritten);
  
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    FillConsoleOutputAttribute(hConsole, csbi.wAttributes,
       conSize, coordScreen, &cCharsWriten);

    SetConsoleCursorPosition(hConsole, coordScreen );
}

static void ConfigureLightsAndDisplay(char* lights, int lightSet)
{
	// Implement.
}

void CConsoleOutput::UpdateDisplay(const int set)
{
	// Implement.
}

void CConsoleOutput::OutputDisplay()
{
	ClearScreen();

	// Implement.
}