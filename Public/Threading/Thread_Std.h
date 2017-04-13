#pragma once

#include "Utility/Platform.h"

#if ETL_STD

#include <thread>
#include <functional>
#include <atomic>
#include "Utility/Types.h"
#include "Utility/Timer.h"

namespace ETL
{
namespace Threading
{
	inline void YieldThread()
	{
		std::this_thread::yield();
	}

	inline void SleepThread(uint32 milliseconds)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
	}

	inline void SleepThreadUntil(uint64 milliseconds)
	{
		SleepThread((uint32)(milliseconds - Timer::Instance().GetMilliseconds()));
	}

#define ETL_THREAD_START_FUNC(func_name) int func_name(void)

	typedef std::function<int(void)> ThreadStartFunc;
	typedef std::thread::id ThreadId;

	class Thread
	{
		ETL_DISABLECOPYING(Thread);
	public:
		Thread();
		Thread(const ThreadStartFunc& startFunc);
		~Thread();
		bool IsExited() const;
		bool HasStarted() const;
		void Start(const ThreadStartFunc& startFunc);
		void Join();
		void Detach();
		inline ThreadId GetThreadId() const { return m_ThreadID; }
		static ThreadId ThisThreadId();

		bool operator==(const Thread& rhs) const;
		bool operator!=(const Thread& rhs) const;

	private:
		std::thread::native_handle_type m_ThreadHandle;
		ThreadId m_ThreadID;
		const ThreadStartFunc m_StartFunc;
		std::atomic<bool> m_HasStarted;
		std::atomic<bool> m_IsRunning;
		std::thread m_Thread;

		static void ThreadStart(Thread* pThread);
	};
}
}

#endif // ETL_STD