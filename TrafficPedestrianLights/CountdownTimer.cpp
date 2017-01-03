#include "CountdownTimer.h"

namespace CountdownTimer
{
	void CTimer::_UpdateTimer()
	{
		end = std::chrono::steady_clock::now();
		elapsed_secs = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
	}

	bool CTimer::_UpdateTrigger(const double DELTA)
	{
		if (elapsed_secs.count() >= DELTA)
		{
			start = std::chrono::steady_clock::now();

			return true;
		}

		return false;
	}


	bool CTimer::UpdateSequence()
	{
		_UpdateTimer();

		return _UpdateTrigger(CYCLE_DELTA);
	}

	bool CTimer::UpdateCountdown()
	{
		_UpdateTimer();

		return _UpdateTrigger(COUNTDOWN_DELTA);
	}

	int CTimer::GetCountdownUpperBound() const
	{
		return TOTAL_SECS;
	}
}