#include "Utility/Platform.h"

#if ETL_MSVC

#include "Threading/Synchronizer_Msvc.h"

namespace ETL
{
namespace Threading
{
	Synchronizer::Synchronizer()
	{
		InitializeSRWLock(&m_WaitLock);
		InitializeConditionVariable(&m_WaitVar);
		m_NumWaiting.store(0);
	}

	Synchronizer::~Synchronizer()
	{
	}

	void Synchronizer::Wait(std::function<bool(void)> waitEnterCondition)
	{
		AcquireSRWLockExclusive(&m_WaitLock);
		++m_NumWaiting;
		if (waitEnterCondition())
			SleepConditionVariableSRW(&m_WaitVar, &m_WaitLock, INFINITE, 0);
		--m_NumWaiting;
		ReleaseSRWLockExclusive(&m_WaitLock);
	}

	void Synchronizer::WakeAll(std::function<bool(void)> wakeCondition)
	{
		AcquireSRWLockExclusive(&m_WaitLock);
		if (wakeCondition())
			WakeAllConditionVariable(&m_WaitVar);
		ReleaseSRWLockExclusive(&m_WaitLock);
	}

	void Synchronizer::WakeOne(std::function<bool(void)> wakeCondition)
	{
		AcquireSRWLockExclusive(&m_WaitLock);
		if (wakeCondition())
			WakeConditionVariable(&m_WaitVar);
		ReleaseSRWLockExclusive(&m_WaitLock);
	}

	uint32 Synchronizer::GetNumThreadsWaiting() const
	{
		return m_NumWaiting;
	}
}
}

#endif // ETL_MSVC