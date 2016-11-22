#ifndef _CONSOLE_OUTPUT_
#define _CONSOLE_OUTPUT_

#include <windows.h>
#include <stdio.h>
#include <cassert>

#define MAXBUF 60

#define RED		FOREGROUND_RED | FOREGROUND_INTENSITY
#define AMBER	FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define GREEN	FOREGROUND_GREEN | FOREGROUND_INTENSITY

#define AMBER_BACKGROUND BACKGROUND_RED | BACKGROUND_GREEN

namespace Console
{
	class CConsoleOutput
	{
	public:

		static CConsoleOutput* ConsoleInst()
		{
			static CConsoleOutput ci;

			return &ci;
		}

		~CConsoleOutput() {}

		void UpdateDisplay(const int set);
		void OutputDisplay();

	private:

		CConsoleOutput() {}
	};
}
#endif