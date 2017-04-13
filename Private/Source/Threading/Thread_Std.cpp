#include "Utility/Platform.h"

#if ETL_STD

#include "Threading/Thread_Std.h"

namespace ETL
{
namespace Threading
{
	void Thread::ThreadStart(Thread *pThread)
	{
		ThreadStartFunc startFunc = pThread->m_StartFunc;
		pThread->m_IsRunning.store(true);
		pThread->m_HasStarted.store(true);
		startFunc();
	}

	Thread::Thread()
		: m_HasStarted(false)
		, m_ThreadHandle(nullptr)
	{

	}

	Thread::Thread(const ThreadStartFunc& startFunc)
	{
		Start(startFunc);
	}

	Thread::~Thread()
	{
		if (m_Thread.joinable())
			m_Thread.join();
	}

	bool Thread::IsExited() const
	{
		return !m_IsRunning;
	}

	bool Thread::HasStarted() const
	{
		return m_HasStarted;
	}

	void Thread::Start(const ThreadStartFunc& startFunc)
	{
		m_HasStarted.store(false);
		m_Thread = std::thread(ThreadStart, this);
		m_ThreadHandle = m_Thread.native_handle();
		m_ThreadID = m_Thread.get_id();
		while (!m_HasStarted)
		{
		}
	}

	void Thread::Join()
	{
		m_Thread.join();
	}

	void Thread::Detach()
	{
		m_Thread.detach();
	}

	ThreadId Thread::ThisThreadId()
	{
		return std::this_thread::get_id();
	}

	bool Thread::operator==(const Thread& rhs) const
	{
		return m_ThreadID == rhs.m_ThreadID;
	}

	bool Thread::operator!=(const Thread& rhs) const
	{
		return m_ThreadID != rhs.m_ThreadID;
	}
}
}

#endif // ETL_STD