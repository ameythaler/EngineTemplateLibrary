#include "Utility/Platform.h"

#if ETL_STD

#include "Threading/RecursiveMutex_Std.h"

namespace ETL
{
namespace Threading
{
	RecursiveMutex::RecursiveMutex()
	{
		m_WriteLockCount.store(0);
		m_ReadCount.store(0);
	}

	void RecursiveMutex::LockRead()
	{
		std::lock_guard<std::recursive_mutex> lock(m_WriteMutex);
		++m_ReadCount;
	}

	void RecursiveMutex::LockWrite()
	{
		m_WriteMutex.lock();
		++m_WriteLockCount;
		m_WaitLock.Wait([this]() {return m_ReadCount > 0; });
	}

	void RecursiveMutex::UnlockRead()
	{
		m_WaitLock.WakeAll([this]() { return --m_ReadCount == 0; });
	}

	void RecursiveMutex::UnlockWrite()
	{
		--m_WriteLockCount;
		m_WriteMutex.unlock();
	}
}
}

#endif // ETL_STD
