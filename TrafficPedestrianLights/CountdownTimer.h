#ifndef _COUNTDOWN_TIMER_
#define _COUNTDOWN_TIMER_

#include <chrono>
#include <ctime>

namespace CountdownTimer
{
	class CTimer
	{
	public:

		CTimer(const unsigned int TIMERDURATION) : duration(TIMERDURATION) 
		{
			// Seed the clock
			start = std::chrono::steady_clock::now();
		}
		~CTimer() {}

		bool UpdateSequence();
		bool UpdateCountdown();

	private:

		std::chrono::steady_clock::time_point start, end;
		std::chrono::duration<double> elapsed_secs;
		const double CYCLE_DELTA = 2.0;

		unsigned int duration;

		void _UpdateTimer();
		bool _UpdateTrigger(const double DELTA);
	};
}

#endif
