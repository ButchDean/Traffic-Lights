#ifndef _COUNTDOWN_TIMER_
#define _COUNTDOWN_TIMER_

#include <chrono>
#include <ctime>

namespace CountdownTimer
{
	class CTimer
	{
	public:

		CTimer(const unsigned int TIMERDURATION) : duration(TIMERDURATION) {}
		~CTimer() {}

	private:

		std::chrono::steady_clock::time_point start, end;
		std::chrono::duration<double> elapsed_secs;
		const double TIME_DELTA = 0.01;

		unsigned int duration;
	};
}

#endif
