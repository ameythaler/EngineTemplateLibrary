#pragma once

#include "Utility/Platform.h"

#if ETL_POSIX

#include "Utility/Types.h"
#include "Utility/Macros.h"
#include <chrono>

namespace ETL
{
namespace Utility
{
	class Timer
	{
		ETL_DECLARE_SINGLETON(Timer);
	public:
		inline void Synchronize() { }
		int64_t GetMilliseconds() const;
		int64_t GetMicroseconds() const;

	private:
		std::chrono::high_resolution_clock::time_point m_StartTime;
	};
}
}

#endif // ETL_POSIX