#pragma once

#include "Utility/Platform.h"

#if ETL_STD

#include <mutex>

namespace ETL
{
namespace Threading
{
	class SimpleMutex
	{
	public:
		void Lock();
		void Unlock();

	private:
		std::mutex m_Mutex;
	};
}
}

#endif // ETL_STD