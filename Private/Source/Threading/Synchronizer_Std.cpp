#include "Utility/Platform.h"

#if ETL_LLVM || ETL_GCC

#include "Threading/Synchronizer_Std.h"

namespace ETL
{
namespace Threading
{
	Synchronizer::Synchronizer()
	{
		m_NumWaiting.store(0);
	}

	Synchronizer::~Synchronizer()
	{

	}

	void Synchronizer::Wait(std::function<bool(void)> waitEnterCondition)
	{
		std::unique_lock<std::mutex> waitLock(m_WaitMutex);
		++m_NumWaiting;
		if (waitEnterCondition())
			m_WaitVar.wait(waitLock);
		--m_NumWaiting;
	}

	void Synchronizer::WakeAll(std::function<bool(void)> wakeCondition)
	{
		std::unique_lock<std::mutex> waitLock(m_WaitMutex);
		if (wakeCondition())
			m_WaitVar.notify_all();
	}

	void Synchronizer::WakeOne(std::function<bool(void)> wakeCondition)
	{
		std::unique_lock<std::mutex> waitLock(m_WaitMutex);
		if (wakeCondition())
			m_WaitVar.notify_one();
	}

	uint32 Synchronizer::GetNumThreadsWaiting() const
	{
		return m_NumWaiting;
	}
}
}

#endif // ETL_LLVM || ETL_GCC