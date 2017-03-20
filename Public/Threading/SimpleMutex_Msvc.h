#pragma once

#include "Utility/Platform.h"

#if ETL_MSVC

#include "Windows.h"

namespace ETL
{
namespace Threading
{
	class SimpleMutex
	{
	public:
		SimpleMutex() : m_Lock(SRWLOCK_INIT) { }
		void Lock();
		void Unlock();

	private:
		SRWLOCK m_Lock;
	};
}
}

#endif // ETL_MSVC