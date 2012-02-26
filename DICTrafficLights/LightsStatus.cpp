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
	// Implement.
}

void CLightsStatus::SetStatusAmber(const int lights)
{
	// Implement.
}

void CLightsStatus::SetStatusGreen(const int lights)
{
	// Implement.
}

void CLightsStatus::ClearStatusRed(const int lights)
{
	// Implement.
}

void CLightsStatus::ClearStatusAmber(const int lights)
{
	// Implement.
}

void CLightsStatus::ClearStatusGreen(const int lights)
{
	// Implement.
}

bool CLightsStatus::GetStatusRed(const int lights) const
{
	// Implement.
}

bool CLightsStatus::GetStatusAmber(const int lights) const
{
	// Implement.
}

bool CLightsStatus::GetStatusGreen(const int lights) const
{
	// Implement.
}

int CLightsStatus::LightsCycled(int lSet)
{
	// Implement.

	return lSet;
}