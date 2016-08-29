#include "LightsStatus.h"

#define SHIFTLEFT(n) (1 << n)

bool CLightsStatus::SystemIsReset()
{
	if(systemStatus)
		return false;

	return true;
}

void CLightsStatus::SetStatusRed(const int lights)
{
	switch(lights)
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

void CLightsStatus::SetStatusAmber(const int lights)
{
	switch(lights)
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

void CLightsStatus::SetStatusGreen(const int lights)
{
	switch(lights)
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

void CLightsStatus::ClearStatusRed(const int lights)
{
	switch(lights)
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

void CLightsStatus::ClearStatusAmber(const int lights)
{
	switch(lights)
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

void CLightsStatus::ClearStatusGreen(const int lights)
{
	switch(lights)
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

bool CLightsStatus::GetStatusRed(const int lights) const
{
	switch(lights)
	{
	case 0:
		if(systemStatus & SHIFTLEFT(2))
			return true;
		else
			return false;
	case 1:
		if(systemStatus & SHIFTLEFT(5))
			return true;
		else
			return false;
	default:
		break;
	}

	return false;
}

bool CLightsStatus::GetStatusAmber(const int lights) const
{
	switch(lights)
	{
	case 0:
		if(systemStatus & SHIFTLEFT(1))
			return true;
		else
			return false;
	case 1:
		if(systemStatus & SHIFTLEFT(4))
			return true;
		else
			return false;
	default:
		break;
	}

	return false;
}

bool CLightsStatus::GetStatusGreen(const int lights) const
{
	switch(lights)
	{
	case 0:
		if(systemStatus & SHIFTLEFT(0))
			return true;
		else
			return false;
	case 1:
		if(systemStatus & SHIFTLEFT(3))
			return true;
		else
			return false;
	default:
		break;
	}

	return false;
}

int CLightsStatus::LightsCycled(int lSet)
{
	if(systemStatus & SHIFTLEFT(0))
		lightsCycled |= SHIFTLEFT(0);

	if((lightsCycled & SHIFTLEFT(0)) && (lSet == 0))
	{
		if(systemStatus & SHIFTLEFT(1))
			lightsCycled |= SHIFTLEFT(1);

		if(systemStatus & SHIFTLEFT(2))
			lightsCycled |= SHIFTLEFT(2);

		if(lightsCycled & SHIFTLEFT(1) &&
			lightsCycled & SHIFTLEFT(2))
		{
			lightsCycled &= ~SHIFTLEFT(0);
			lightsCycled &= ~SHIFTLEFT(1);
			lightsCycled &= ~SHIFTLEFT(2);

			return 1;
		}
	}

	if(systemStatus & SHIFTLEFT(3))
		lightsCycled |= SHIFTLEFT(3);

	if((lightsCycled & SHIFTLEFT(3)) && (lSet == 1))
	{
		if(systemStatus & SHIFTLEFT(4))
			lightsCycled |= SHIFTLEFT(4);

		if(systemStatus & SHIFTLEFT(5))
			lightsCycled |= SHIFTLEFT(5);

		if(lightsCycled & SHIFTLEFT(4) &&
			lightsCycled & SHIFTLEFT(5))
		{
			lightsCycled &= ~SHIFTLEFT(3);
			lightsCycled &= ~SHIFTLEFT(4);
			lightsCycled &= ~SHIFTLEFT(5);

			return 0;
		}
	}

	return lSet;
}