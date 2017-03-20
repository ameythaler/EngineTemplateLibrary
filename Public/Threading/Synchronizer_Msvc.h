#pragma once

#include "Utility/Platform.h"

#if ETL_MSVC

#include "Utility/Types.h"
#include "Windows.h"
#include <functional>
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
		SRWLOCK m_WaitLock;
		CONDITION_VARIABLE m_WaitVar;
		mutable std::atomic<int32> m_NumWaiting;
	};
}
}

#endif // ETL_MSVC