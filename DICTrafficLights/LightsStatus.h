#ifndef _LIGHTS_STATUS_
#define _LIGHTS_STATUS_

#define ZERO					0x00

class CLightsStatus
{
public:

	static CLightsStatus* StatusDetail()
	{
		static CLightsStatus ls;

		return &ls;
	}

	~CLightsStatus(){}

	bool SystemIsReset();

	void SetStatusRed(const int lights);
	void SetStatusAmber(const int lights);
	void SetStatusGreen(const int lights);

	void ClearStatusRed(const int lights);
	void ClearStatusAmber(const int lights);
	void ClearStatusGreen(const int lights);

	bool GetStatusRed(const int lights) const;
	bool GetStatusAmber(const int lights) const;
	bool GetStatusGreen(const int lights) const;

	int LightsCycled(int lSet);

	unsigned char GetSystemStatus() const
	{
		return systemStatus;
	}

private:

	CLightsStatus()
	{
		systemStatus ^= systemStatus;
		lightsCycled ^= lightsCycled;
	}

	unsigned char systemStatus;
	unsigned char lightsCycled;

};

#endif