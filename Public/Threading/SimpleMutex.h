#pragma once

#include "Utility/Platform.h"

#if ETL_MSVC

#include "Threading/SimpleMutex_Msvc.h"

#else

#include "Threading/SimpleMutex_Std.h"

#endif // ETL_MSVC

namespace ETL
{
namespace Threading
{
	struct SimpleScopeLock
	{
		SimpleScopeLock(SimpleMutex& simpleMutex);
		~SimpleScopeLock();

	private:
		SimpleMutex& m_Mutex;
	};
}
}