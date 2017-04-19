#include "Utility/Platform.h"

#if ETL_STD

#include "Threading/SimpleMutex_Std.h"

namespace ETL
{
namespace Threading
{
	void SimpleMutex::Lock()
	{
		m_Mutex.lock();
	}

	void SimpleMutex::Unlock()
	{
		m_Mutex.unlock();
	}
}
}

#endif // ETL_STD
