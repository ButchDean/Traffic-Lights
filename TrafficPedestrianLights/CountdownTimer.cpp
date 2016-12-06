#include "CountdownTimer.h"

namespace CountdownTimer
{
	bool CTimer::UpdateSequence()
	{
		end = std::chrono::steady_clock::now();
		elapsed_secs = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

		if(elapsed_secs.count() >= TIME_DELTA)
		{
			start = std::chrono::steady_clock::now();

			return true;
		}

		return false;
	}
}