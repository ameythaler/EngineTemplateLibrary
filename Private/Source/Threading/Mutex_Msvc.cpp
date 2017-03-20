#include "Utility/Platform.h"

#if ETL_MSVC

#include "Threading/Mutex_Msvc.h"

namespace ETL
{
namespace Threading
{
	Mutex::Mutex() : m_WriteLock(SRWLOCK_INIT)
	{
		m_ReadCount.store(0);
		m_bIsWriteLocked.store(false);
	}

	void Mutex::LockRead()
	{
		AcquireSRWLockExclusive(&m_WriteLock);
		++m_ReadCount;
		ReleaseSRWLockExclusive(&m_WriteLock);
	}

	void Mutex::LockWrite()
	{
		AcquireSRWLockExclusive(&m_WriteLock);
		m_WaitLock.Wait([this]() { return m_ReadCount > 0; });
		m_bIsWriteLocked.store(true);
	}

	void Mutex::UnlockRead()
	{
		m_WaitLock.WakeAll([this]() {
			--m_ReadCount;
			return m_ReadCount == 0; 
		});
	}

	void Mutex::UnlockWrite()
	{
		m_bIsWriteLocked.store(false);
		ReleaseSRWLockExclusive(&m_WriteLock);
	}
}
}

#endif