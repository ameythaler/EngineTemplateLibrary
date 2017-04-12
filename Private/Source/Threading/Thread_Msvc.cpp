#include "Utility/Platform.h"

#if ETL_MSVC

#include "Threading/Thread_Msvc.h"

using ETL::Utility::Timer;

namespace ETL
{
namespace Threading
{
	void SleepThreadUntil(uint64 milliseconds)
	{
		uint64 curTime = Timer::Instance().GetMilliseconds();
		if (milliseconds > curTime)
			SleepThread((uint32)(milliseconds - curTime));
	}

	DWORD WINAPI Thread::ThreadStart(LPVOID threadParams)
	{
		Thread* pThread = (Thread*)threadParams;
		ThreadStartFunc startFunc = pThread->m_StartFunc;
		InterlockedExchange(&pThread->m_IsStarted, 1);
		return startFunc();
	}

	Thread::Thread()
		: m_ThreadHandle(nullptr)
		, m_ThreadID(0)
		, m_StartFunc(nullptr)
		, m_IsStarted(0)
	{
	}

	Thread::Thread(const ThreadStartFunc& startFunc)
	{
		Start(startFunc);
	}

	Thread::~Thread()
	{
		if (m_ThreadHandle && m_StartFunc) // m_StartFunc will be null if thread was created via ThisThread()
			Join();
	}

	bool Thread::IsExited() const
	{
		return WaitForSingleObject(m_ThreadHandle, 0) == WAIT_OBJECT_0;
	}

	bool Thread::IsStarted() const
	{
		return InterlockedCompareExchange(&m_IsStarted, 0, 0) == 1;
	}

	void Thread::Start(const ThreadStartFunc& startFunc)
	{
		m_StartFunc = startFunc;
		InterlockedExchange(&m_IsStarted, 0);
		m_ThreadHandle = CreateThread(NULL, 0, &ThreadStart, (LPVOID)this, 0, (LPDWORD)&m_ThreadID);
		while (InterlockedCompareExchange(&m_IsStarted, 1, 1) != 1)
		{
		}
	}

	void Thread::Join()
	{
		if (m_ThreadHandle)
			WaitForSingleObject(m_ThreadHandle, INFINITE);
		m_ThreadHandle = nullptr;
	}

	void Thread::Detach()
	{
		if (m_ThreadHandle)
			CloseHandle(m_ThreadHandle);
		m_ThreadHandle = nullptr;
	}

	const Thread&& Thread::ThisThread()
	{
		Thread thisThread;
		thisThread.m_ThreadID = GetCurrentThreadId();
		thisThread.m_ThreadHandle = GetCurrentThread();
		thisThread.m_IsStarted = true;
		return std::move(thisThread);
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

#endif // ETL_MSVC