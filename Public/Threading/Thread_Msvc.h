#pragma once

#include "Utility/Platform.h"

#if ETL_MSVC

#include "Windows.h"
#include <functional>
#include "Utility/Types.h"
#include "Utility/Timer.h"

namespace ETL
{
namespace Threading
{
	inline void YieldThread()
	{
		SwitchToThread();
	}

	inline void SleepThread(uint32 milliseconds)
	{
		Sleep(milliseconds);
	}

	void SleepThreadUntil(uint64 milliseconds);

#define ETL_THREAD_START_FUNC(func_name) int32 func_name(void)

	typedef std::function<int32(void)> ThreadStartFunc;
	typedef uint32 ThreadId;

	class Thread
	{
		ETL_DISABLECOPYING(Thread);
	public:
		Thread();
		Thread(const ThreadStartFunc& startFunc);
		~Thread();
		bool IsExited() const;
		bool IsStarted() const;
		void Start(const ThreadStartFunc& startFunc);
		void Join();
		void Detach();
		inline ThreadId GetThreadId() const { return m_ThreadID; }
		static ThreadId ThisThreadId();

		bool operator==(const Thread& rhs) const;
		bool operator!=(const Thread& rhs) const;

	private:
		HANDLE m_ThreadHandle;
		ThreadId m_ThreadID;
		ThreadStartFunc m_StartFunc;
		mutable LONG m_IsStarted;

		static DWORD WINAPI ThreadStart(LPVOID threadParams);
	};
}
}

#endif // ETL_MSVC