#ifndef _COUNTDOWN_TIMER_
#define _COUNTDOWN_TIMER_

#include <chrono>
#include <ctime>

namespace CountdownTimer
{
	class CTimer
	{
	public:

		CTimer()
		{
			// Seed the clock
			start = std::chrono::steady_clock::now();
		}
		~CTimer() {}

		bool UpdateSequence();
		bool UpdateCountdown();

		int GetCountdownUpperBound() const;

	private:

		std::chrono::steady_clock::time_point start, end;
		std::chrono::duration<double> elapsed_secs;
		const double CYCLE_DELTA = 2.0;
		const double COUNTDOWN_DELTA = 1.0;
		const unsigned int TOTAL_SECS = 13;

		void _UpdateTimer();
		bool _UpdateTrigger(const double DELTA);
	};
}

#endif
