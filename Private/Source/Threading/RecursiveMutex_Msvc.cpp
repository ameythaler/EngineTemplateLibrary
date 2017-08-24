#include "Utility/Platform.h"

#if ETL_MSVC

#include "Threading/RecursiveMutex_Msvc.h"

namespace ETL
{
namespace Threading
{
	RecursiveMutex::RecursiveMutex()
	{
		InitializeCriticalSectionAndSpinCount(&m_WriteLock, 100);
		m_ReadCount.store(0);
		m_WriteLockCount.store(0);
	}

	void RecursiveMutex::LockRead()
	{
		EnterCriticalSection(&m_WriteLock);
		++m_ReadCount;
		LeaveCriticalSection(&m_WriteLock);
	}

	void RecursiveMutex::LockWrite()
	{
		EnterCriticalSection(&m_WriteLock);
		m_WaitLock.Wait([this]() { return m_ReadCount > 0; });
		++m_WriteLockCount;
	}

	void RecursiveMutex::UnlockRead()
	{
		m_WaitLock.WakeAll([this]() {
			--m_ReadCount;
			return m_ReadCount == 0; });
	}

	void RecursiveMutex::UnlockWrite()
	{
		--m_WriteLockCount;
		LeaveCriticalSection(&m_WriteLock);
	}
}
}

#endif // ETL_MSVC