#include "Utility/Platform.h"

#if ETL_WIN

#include "Utility/Timer_Win.h"
#include <windows.h>

namespace
{
	const ETL::int64 cToMilliseconds = 10000;
	const ETL::int64 cToMicroseconds = 10;
}

namespace ETL
{
namespace Utility
{
	ETL_IMPLEMENT_SINGLETON(Timer);

	Timer::Timer()
	{
		Synchronize();
	}

	Timer::~Timer()
	{

	}

	void Timer::Synchronize()
	{
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		m_nFrequency = frequency.QuadPart;
	}

	int64 Timer::GetMilliseconds() const
	{
		int64 nRawTime;
		RawTime(nRawTime);
		return nRawTime / cToMilliseconds;
	}

	int64 Timer::GetMicroseconds() const
	{
		int64 nRawTime;
		RawTime(nRawTime);
		return nRawTime / cToMicroseconds;
	}

	void Timer::RawTime(int64& nRawTime) const
	{
		LARGE_INTEGER curTime;
		QueryPerformanceCounter(&curTime);
		nRawTime = curTime.QuadPart;
	}
}
}

#endif // ETL_WIN