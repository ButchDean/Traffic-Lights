#include "CountdownTimer.h"

namespace CountdownTimer
{
	void CTimer::_UpdateTimer()
	{
		end = std::chrono::steady_clock::now();
		elapsed_secs = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
	}

	bool CTimer::UpdateSequence()
	{
		_UpdateTimer();

		if(elapsed_secs.count() >= CYCLE_DELTA)
		{
			start = std::chrono::steady_clock::now();

			return true;
		}

		return false;
	}
}