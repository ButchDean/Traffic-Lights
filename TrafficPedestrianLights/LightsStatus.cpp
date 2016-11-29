#include "LightsStatus.h"

#define SHIFTLEFT(n) (1 << n)

namespace Signals
{
	bool CLightsStatus::SystemIsReset()
	{
		if (systemStatus)
			return false;

		return true;
	}

	void CLightsStatus::SetStatusWalk(const unsigned short lights)
	{
		switch (lights)
		{
		case 0:
			systemStatus |= SHIFTLEFT(6);
			break;
		case 1:
			systemStatus |= SHIFTLEFT(7);
			break;
		default:
			break;
		}
	}

	void CLightsStatus::SetStatusRed(const unsigned short lights)
	{
		switch (lights)
		{
		case 0:
			systemStatus |= SHIFTLEFT(2);
			break;
		case 1:
			systemStatus |= SHIFTLEFT(5);
			break;
		default:
			break;
		}
	}

	void CLightsStatus::SetStatusAmber(const unsigned short lights)
	{
		switch (lights)
		{
		case 0:
			systemStatus |= SHIFTLEFT(1);
			break;
		case 1:
			systemStatus |= SHIFTLEFT(4);
			break;
		default:
			break;
		}
	}

	void CLightsStatus::SetStatusGreen(const unsigned short lights)
	{
		switch (lights)
		{
		case 0:
			systemStatus |= SHIFTLEFT(0);
			break;
		case 1:
			systemStatus |= SHIFTLEFT(3);
			break;
		default:
			break;
		}
	}

	void CLightsStatus::ClearStatusWalk(const unsigned short lights)
	{
		switch (lights)
		{
		case 0:
			systemStatus &= ~SHIFTLEFT(6);
			break;
		case 1:
			systemStatus &= ~SHIFTLEFT(7);
			break;
		default:
			break;
		}
	}

	void CLightsStatus::ClearStatusRed(const unsigned short lights)
	{
		switch (lights)
		{
		case 0:
			systemStatus &= ~SHIFTLEFT(2);
			break;
		case 1:
			systemStatus &= ~SHIFTLEFT(5);
			break;
		default:
			break;
		}
	}

	void CLightsStatus::ClearStatusAmber(const unsigned short lights)
	{
		switch (lights)
		{
		case 0:
			systemStatus &= ~SHIFTLEFT(1);
			break;
		case 1:
			systemStatus &= ~SHIFTLEFT(4);
			break;
		default:
			break;
		}
	}

	void CLightsStatus::ClearStatusGreen(const unsigned short lights)
	{
		switch (lights)
		{
		case 0:
			systemStatus &= ~SHIFTLEFT(0);
			break;
		case 1:
			systemStatus &= ~SHIFTLEFT(3);
			break;
		default:
			break;
		}
	}

	bool CLightsStatus::GetStatusWalk(const unsigned short lights) const
	{
		switch (lights)
		{
		case 0:
			if (systemStatus & SHIFTLEFT(6))
				return true;
			else
				return false;
		case 1:
			if (systemStatus & SHIFTLEFT(7))
				return true;
			else
				return false;
		default:
			break;
		}

		return false;
	}

	bool CLightsStatus::GetStatusRed(const unsigned short lights) const
	{
		switch (lights)
		{
		case 0:
			if (systemStatus & SHIFTLEFT(2))
				return true;
			else
				return false;
		case 1:
			if (systemStatus & SHIFTLEFT(5))
				return true;
			else
				return false;
		default:
			break;
		}

		return false;
	}

	bool CLightsStatus::GetStatusAmber(const unsigned short lights) const
	{
		switch (lights)
		{
		case 0:
			if (systemStatus & SHIFTLEFT(1))
				return true;
			else
				return false;
		case 1:
			if (systemStatus & SHIFTLEFT(4))
				return true;
			else
				return false;
		default:
			break;
		}

		return false;
	}

	bool CLightsStatus::GetStatusGreen(const unsigned short lights) const
	{
		switch (lights)
		{
		case 0:
			if (systemStatus & SHIFTLEFT(0))
				return true;
			else
				return false;
		case 1:
			if (systemStatus & SHIFTLEFT(3))
				return true;
			else
				return false;
		default:
			break;
		}

		return false;
	}

	unsigned short CLightsStatus::CycleLights(unsigned short lSet)
	{
		// Switch from cycling first set of signals to the second set.
		if (lSet == 0 && GetStatusRed(0))
			return 1;

		// Switch from cycling second set of signals to the first.
		if (lSet == 1 && GetStatusRed(1))
			return 0;

		return lSet;
	}
}