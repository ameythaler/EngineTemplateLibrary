#include "Utility/Platform.h"

#if ETL_STD

#include "Threading/Mutex_Std.h"

namespace ETL
{
namespace Threading
{
	Mutex::Mutex()
	{
		m_bIsWriteLocked.store(false);
		m_ReadCount.store(0);
	}

	void Mutex::LockRead()
	{
		std::lock_guard<std::mutex> lock(m_WriteMutex);
		++m_ReadCount;
	}

	void Mutex::LockWrite()
	{
		m_WriteMutex.lock();
		m_bIsWriteLocked.store(true);
		m_WaitLock.Wait([this]() {return m_ReadCount > 0; });
	}

	void Mutex::UnlockRead()
	{
		m_WaitLock.WakeAll([this]() { return --m_ReadCount == 0; });
	}

	void Mutex::UnlockWrite()
	{
		m_bIsWriteLocked.store(false);
		m_WriteMutex.unlock();
	}
}
}

#endif // ETL_STD
