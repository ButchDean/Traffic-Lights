#ifndef _LIGHTS_STATUS_
#define _LIGHTS_STATUS_

#define ZERO					0x00

namespace Signals
{
	class CLightsStatus
	{
	public:

		static CLightsStatus* StatusDetail()
		{
			static CLightsStatus ls;

			return &ls;
		}

		~CLightsStatus() {}

		bool SystemIsReset();

		void SetStatusWalk(const unsigned short lights);
		void SetStatusRed(const unsigned short lights);
		void SetStatusAmber(const unsigned short lights);
		void SetStatusGreen(const unsigned short lights);

		void ClearStatusWalk(const unsigned short lights);
		void ClearStatusRed(const unsigned short lights);
		void ClearStatusAmber(const unsigned short lights);
		void ClearStatusGreen(const unsigned short lights);

		bool GetStatusWalk(const unsigned short lights) const;
		bool GetStatusRed(const unsigned short lights) const;
		bool GetStatusAmber(const unsigned short lights) const;
		bool GetStatusGreen(const unsigned short lights) const;

		unsigned short CycleLights(unsigned short lSet);

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

		unsigned char systemStatus; // Bit 2, 5 Red. Bits 1, 4 Amber. Bits 0, 3 Green. Bits 6, 7 Walk/Don't Walk.
		unsigned char lightsCycled;

	};
}

#endif