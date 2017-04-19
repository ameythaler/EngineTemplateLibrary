#pragma once

#include "Utility/Platform.h"

#if ETL_STD

#include "Utility/Types.h"
#include <mutex>
#include <condition_variable>
#include <atomic>

namespace ETL
{
namespace Threading
{
	class Synchronizer
	{
	public:
		Synchronizer();
		~Synchronizer();

		void Wait(std::function<bool(void)> waitEnterCondition);
		void WakeOne(std::function<bool(void)> wakeCondition);
		void WakeAll(std::function<bool(void)> wakeCondition);

		uint32 GetNumThreadsWaiting() const;

	private:
		std::mutex m_WaitMutex;
		std::condition_variable m_WaitVar;
		std::atomic<uint32_t> m_NumWaiting;
	};
}
}

#endif // ETL_STD