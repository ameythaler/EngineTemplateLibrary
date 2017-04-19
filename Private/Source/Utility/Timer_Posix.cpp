#include "Utility/Platform.h"

#if ETL_POSIX

#include "Utility/Timer_Posix.h"

namespace ETL
{
namespace Utility
{
	ETL_IMPLEMENT_SINGLETON(Timer);

	typedef std::chrono::high_resolution_clock::time_point TimePoint;
	typedef std::chrono::high_resolution_clock Clock;

	Timer::Timer()
	{
		m_StartTime = Clock::now();
	}

	Timer::~Timer()
	{

	}

	int64 Timer::GetMilliseconds() const
	{
		TimePoint curTime = Clock::now();
		std::chrono::milliseconds dur = std::chrono::duration_cast<std::chrono::milliseconds>(curTime - m_StartTime);
		return dur.count();
	}

	int64 Timer::GetMicroseconds() const
	{
		TimePoint curTime = Clock::now();
		std::chrono::microseconds dur = std::chrono::duration_cast<std::chrono::microseconds>(curTime - m_StartTime);
		return dur.count();
	}
}
}

#endif // ETL_POSIX
