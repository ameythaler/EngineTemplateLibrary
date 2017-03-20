#pragma once

#include "Utility/Platform.h"

#if ETL_STD

#include "Threading/Lockable.h"
#include "Threading/Synchronizer.h"
#include "Utility/Types.h"
#include <mutex>
#include <atomic>
#include <thread>

namespace ETL
{
namespace Threading
{
	class Mutex : public ILockable
	{
	public:
		Mutex();
		virtual void LockRead();
		virtual void LockWrite();
		virtual void UnlockRead();
		virtual void UnlockWrite();
		inline virtual uint32 GetReadLockCount() const { return m_ReadCount; }
		inline virtual bool IsWriteLocked() const { return m_bIsWriteLocked; }

	private:
		std::mutex m_WriteMutex;
		Synchronizer m_WaitLock;
		std::atomic<uint32> m_ReadCount;
		std::atomic<bool> m_bIsWriteLocked;
	};
}
}

#endif // ETL_STD