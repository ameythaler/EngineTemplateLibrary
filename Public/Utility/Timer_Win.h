#pragma once

#include "Utility/Platform.h"

#if ETL_WIN

#include "Utility/Types.h"
#include "Utility/Macros.h"

namespace ETL
{
namespace Utility
{
	class Timer
	{
		ETL_DECLARE_SINGLETON(Timer);
	public:
		void Synchronize();
		int64 GetMilliseconds() const;
		int64 GetMicroseconds() const;

	private:
		int64 m_nFrequency;

		void RawTime(int64& nRawTime) const;
	};
}
}

#endif // ETL_WIN